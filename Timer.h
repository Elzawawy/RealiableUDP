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

public:
    template<class T,class _Args>
    void StartTimer(void (*f)() ,_Args arg){
        //acquire the mutex lock and initialize the timer_stop_
        std::unique_lock<std::mutex> lck(this->stopping_timer_mutex_);
        timer_stop_=false;
        lck.unlock();
        thread th(&Timer::TimerCounter,this,f,arg);//launch a thread to count
        th.detach();

    }
    void StopTimer();
private:
    int timer_duration_ms_;
    template<class _Arg>
    void* TimerCounter(std::function<void (void)> f,_Arg arg){
        std::chrono::steady_clock::time_point timer_end_=
                std::chrono::steady_clock::now()+std::chrono::milliseconds(timer_duration_ms_);

        while(std::chrono::steady_clock::now()<timer_end_){
            std::lock_guard<std::mutex> lck(this->stopping_timer_mutex_);
            if(timer_stop_){

                return nullptr;
            }
        };

        thread th(f,arg);
        th.detach();

        return nullptr;
    }
    mutex stopping_timer_mutex_;
    bool timer_stop_;

public:
    Timer(int timer_duration_ms);

};


#endif //REALIABLEUDP_TIMER_H
