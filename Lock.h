//
// Created by Alexander Chan-Nui on 10/23/23.
//

#ifndef CS4348OS_PROJECT2_LOCK_H
#define CS4348OS_PROJECT2_LOCK_H
#include "Sem.h"


class Lock {
public:
    Lock(Sem& sem_):sem(sem_){
       sem.lock();
    }

    ~Lock(){
       sem.unlock();
    }

private:
    Sem& sem;

};


#endif //CS4348OS_PROJECT2_LOCK_H
