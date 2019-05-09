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
    template<typename _Callable,typename... _Args>
    void StartTimer(_Callable f,_Args&&... args);
    void StopTimer();
private:
    int timer_duration_ms_;
    template<typename _Callable,typename... _Args>
    void* TimerCounter(_Callable f,_Args&&... args);
    mutex stopping_timer_mutex_;
    bool timer_stop_;

public:
    Timer(int timer_duration_ms);

};


#endif //REALIABLEUDP_TIMER_H
