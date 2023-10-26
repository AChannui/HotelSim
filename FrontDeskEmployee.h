//
// Created by Alexander Chan-Nui on 10/23/23.
//

#ifndef CS4348OS_PROJECT2_FRONTDESKEMPLOYEE_H
#define CS4348OS_PROJECT2_FRONTDESKEMPLOYEE_H
#include "iostream"
#include "RoomCount.h"
#include "GuestQueue.h"
#include "Guest.h"
#include "Logger.h"


class FrontDeskEmployee {
public:
    FrontDeskEmployee(int employee_id_, GuestQueue &check_in_queue_, RoomCount &room_count_, Logger &logger_);

    int get_employee_id(){
       Lock lock(mutex_sem);
       return employee_id;
    }

    void start();

    void loop();

private:
    int employee_id;
    RoomCount &room_count;
    GuestQueue &check_in_queue;
    Sem mutex_sem = Sem(1);
    pthread_t ptid;
    Logger &logger;

};


#endif //CS4348OS_PROJECT2_FRONTDESKEMPLOYEE_H
