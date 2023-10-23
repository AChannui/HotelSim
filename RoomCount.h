//
// Created by Alexander Chan-Nui on 10/23/23.
//

#ifndef CS4348OS_PROJECT2_ROOMCOUNT_H
#define CS4348OS_PROJECT2_ROOMCOUNT_H
#include "Lock.h"


class RoomCount {
public:
    int get_count(){
       Lock lock(mutex_sem);
       int temp = count;
       count++;
       return temp;
    }

private:
    int count = 1;
    Sem mutex_sem = Sem(0);

};


#endif //CS4348OS_PROJECT2_ROOMCOUNT_H
