//
// Created by Alexander Chan-Nui on 10/23/23.
//

#ifndef CS4348OS_PROJECT2_SEM_H
#define CS4348OS_PROJECT2_SEM_H

#include <cstring>
#include "semaphore.h"
#include "stdexcept"


class Sem {
public:

    Sem(int sem_value) {
       int rc = sem_init(&sem, 0, sem_value); // creation of semaphore
       if (rc != 0) {
          // bug testing tools
          std::cout << "rc=" << rc << std::endl;
          std::cout << "errno=" << errno << " " << strerror(errno) << std::endl;
          throw std::runtime_error("Failed to initialize mutex_sem");
       }
    }

    ~Sem() {
       sem_destroy(&sem);
    }

    void wait() {
       if (sem_wait(&sem) != 0) {
          throw std::runtime_error("Failed to wait");
       }
    }

    void post() {
       if (sem_post(&sem) != 0) {
          throw std::runtime_error("Failed to Post");
       }
    }

private:
    sem_t sem;


};


#endif //CS4348OS_PROJECT2_SEM_H
