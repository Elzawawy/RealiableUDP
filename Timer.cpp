//
// Created by omar_swidan on 08/05/19.
//

#include "Timer.h"
#include <chrono>
#include <signal.h>
#include <unistd.h>


/*must be called by a child process and the parent must implement a signal handler for SIGUSR1*/

void Timer::StopTimer() {
    std::unique_lock<std::mutex> lck(this->stopping_timer_mutex_);
    timer_stop_=true;
}
template<typename _Callable,typename... _Args>
void Timer::StartTimer(_Callable f,_Args&&... args) {
    //acquire the mutex lock and initialize the timer_stop_
    std::unique_lock<std::mutex> lck(this->stopping_timer_mutex_);
    timer_stop_=false;
    lck.unlock();
    thread th(Timer::TimerCounter(f),this,std::forward(args)...);//launch a thread to count
    th.detach();

}

Timer::Timer(int timer_duration_ms) : timer_duration_ms_(timer_duration_ms),timer_stop_(false) {}
template<typename _Callable,typename... _Args>
void *Timer::TimerCounter(_Callable f,_Args&&... args) {

    std::chrono::steady_clock::time_point timer_end_=
            std::chrono::steady_clock::now()+std::chrono::milliseconds(timer_duration_ms_);
    std::unique_lock<std::mutex> lck(this->stopping_timer_mutex_);
    while(std::chrono::steady_clock::now()<timer_end_){
        lck.lock();
        if(timer_stop_){
            return nullptr;
        }
        lck.unlock();

    };

    thread th(f,std::forward(args)...);
    th.detach();

    return nullptr;
}

