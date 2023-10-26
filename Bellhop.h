//
// Created by Alexander Chan-Nui on 10/25/23.
//

#ifndef CS4348OS_PROJECT2_BELLHOP_H
#define CS4348OS_PROJECT2_BELLHOP_H
#include <iostream>
#include <sstream>

#include "GuestQueue.h"
#include "Logger.h"


class Bellhop {
public:
    Bellhop(int employee_id_, GuestQueue &bellhop_queue_, Logger &logger_);

    void guest_signal(){
       Lock lock(mutex_sem);
       guest_sem.post();
    }

    int get_employee_id(){
       Lock lock(mutex_sem);
       return employee_id;
    }

    void start();

    void loop();

private:
    int employee_id;
    GuestQueue &bellhop_queue;
    Sem mutex_sem;
    Sem guest_sem;
    pthread_t ptid;
    Logger &logger;


};





#endif //CS4348OS_PROJECT2_BELLHOP_H
