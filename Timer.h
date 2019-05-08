//
// Created by omar_swidan on 08/05/19.
//

#ifndef REALIABLEUDP_TIMER_H
#define REALIABLEUDP_TIMER_H


#include <signal.h>

class Timer {

public:
    void StartTimer(int timer_duration_ms_);
    void StopTimer(pid_t timer_process_id_);


};


#endif //REALIABLEUDP_TIMER_H
