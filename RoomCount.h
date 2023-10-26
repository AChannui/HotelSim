//
// Created by Alexander Chan-Nui on 10/23/23.
//

#ifndef CS4348OS_PROJECT2_ROOMCOUNT_H
#define CS4348OS_PROJECT2_ROOMCOUNT_H
#include "Lock.h"


class RoomCount {
public:
    RoomCount(): count(1), mutex_sem(Sem(1)){}

    int get_count(){
       Lock lock(mutex_sem);
       int temp = count;
       count++;
       return temp;
    }

private:
    int count;
    Sem mutex_sem;

};


#endif //CS4348OS_PROJECT2_ROOMCOUNT_H
