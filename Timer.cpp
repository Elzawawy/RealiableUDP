//
// Created by omar_swidan on 08/05/19.
//

#include "Timer.h"
#include <chrono>
#include <signal.h>
#include <unistd.h>


/*must be called by a child process and the parent must implement a signal handler for SIGUSR1*/
void Timer::StartTimer(int timer_duration_ms_) {
    std::chrono::steady_clock::time_point timer_end_=
            std::chrono::steady_clock::now()+std::chrono::milliseconds(timer_duration_ms_);
    while(std::chrono::steady_clock::now()<timer_end_);
    kill(getppid(),SIGUSR1);
}

void Timer::StopTimer(pid_t timer_process_id_) {
    kill(timer_process_id_,SIGKILL);
}

