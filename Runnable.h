//
// Created by Alexander Chan-Nui on 10/28/23.
//

#ifndef CS4348OS_PROJECT2_RUNNABLE_H
#define CS4348OS_PROJECT2_RUNNABLE_H
#include <pthread.h>


class Runnable {
public:
    void start();

    void join(){
       pthread_join(ptid, nullptr);
    }

    virtual void loop() = 0;

    virtual ~Runnable(){}

private:
    pthread_t ptid;

};


#endif //CS4348OS_PROJECT2_RUNNABLE_H
