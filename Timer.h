//
// Created by omar_swidan on 08/05/19.
//

#ifndef REALIABLEUDP_TIMER_H
#define REALIABLEUDP_TIMER_H



#include <signal.h>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Timer {
private:
    int timer_duration_ms_;
    template<typename _Callable, typename... _Args>
    void TimerCounter(_Callable &&f,_Args&&... arg){

        std::chrono::steady_clock::time_point timer_end_=
                std::chrono::steady_clock::now()+std::chrono::milliseconds(timer_duration_ms_);

        while(std::chrono::steady_clock::now()<timer_end_) {
            std::lock_guard<std::mutex> lck(this->stopping_timer_mutex_);
            if(timer_stop_){

                return ;
            }
        };

        


    }
    mutex stopping_timer_mutex_;
    bool timer_stop_;



public:
    template<typename _Callable, typename... _Args>
    void StartTimer(_Callable&& f , _Args&&... args){
        //acquire the mutex lock and initialize the timer_stop_
        std::unique_lock<std::mutex> lck(this->stopping_timer_mutex_);
        timer_stop_=false;
        lck.unlock();
        //auto x = [this,f,args...] (){TimerCounter(f, args...);};

        thread th( &Timer::TimerCounter<std::decay_t<_Callable>,std::decay_t<_Args>...>,this,
                std::forward<_Callable>(f), std::forward<_Args>(args)...);//launch a thread to count
        th.detach();

    }
    void StopTimer();

public:
    Timer(int timer_duration_ms);

};


#endif //REALIABLEUDP_TIMER_H
