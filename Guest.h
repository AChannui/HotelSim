//
// Created by Alexander Chan-Nui on 10/23/23.
//

#ifndef CS4348OS_PROJECT2_GUEST_H
#define CS4348OS_PROJECT2_GUEST_H

#include <iostream>
#include <sstream>

#include "GuestQueue.h"
#include "Logger.h"

class Bellhop;


class Guest {
public:
    Guest(int guest_numb_, int bag_numb_, GuestQueue &check_in_queue_, GuestQueue &bellhop_queue_,
          GuestQueue &exit_queue_, Logger &logger_);

    int get_bag_numb() {
       Lock lock(mutex_sem);
       return bag_numb;
    }

    void set_room_key(int input) {
       Lock lock(mutex_sem);
       room_numb = input;
    }

    void signal_room_key() {
       Lock lock(mutex_sem);
       room_key_sem.post();
    }

    void signal_bag() {
       Lock lock(mutex_sem);
       bag_sem.post();
    }

    void set_front_desk_helper(int input) {
       Lock lock(mutex_sem);
       front_desk_helper = input;
    }

    pthread_t get_ptid() {
       Lock lock(mutex_sem);
       return ptid;
    }

    int get_guest_id() {
       Lock lock(mutex_sem);
       return guest_id;
    }

    int get_room_numb() {
       Lock lock(mutex_sem);
       return room_numb;
    }

    void bellhop_help(Bellhop *bellhop_) {
       Lock lock(mutex_sem);
       bellhop = bellhop_;
    }

    void start();

    void loop();


private:
    int room_numb;
    int bag_numb;
    int guest_id;
    int front_desk_helper;
    int bag_limit;
    Sem mutex_sem = Sem(1);
    Sem bag_sem = Sem(0);
    Sem room_key_sem = Sem(0);
    pthread_t ptid;
    GuestQueue &check_in_queue;
    GuestQueue &bellhop_queue;
    GuestQueue &exit_queue;
    Logger &logger;
    Bellhop *bellhop;

};


#endif //CS4348OS_PROJECT2_GUEST_H
