//
// Created by Alexander Chan-Nui on 10/23/23.
//

#ifndef CS4348OS_PROJECT2_SEM_H
#define CS4348OS_PROJECT2_SEM_H
#include "semaphore.h"
#include "stdexcept"


class Sem {
public:

    Sem(int sem_value){
       if(sem_init(&sem, 0, sem_value) != 0){
          throw std::runtime_error("Failed to initialize mutex_sem")
       }
    }

    ~Sem(){
       if(sem_destroy(&sem) != 0){
          throw std::runtime_error("Failed to destroy mutex_sem");
       }
    }

    void wait(){
       if(sem_wait(&sem) != 0){
          throw std::runtime_error("Failed to wait");
       }
    }

    void post(){
       if(sem_post(&sem) != 0){
          throw std::runtime_error("Failed to Post");
       }
    }

private:
    sem_t sem;


};


#endif //CS4348OS_PROJECT2_SEM_H
