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


Timer::Timer(int timer_duration_ms) : timer_duration_ms_(timer_duration_ms),timer_stop_(false) {}


