//
// Created by Alexander Chan-Nui on 10/23/23.
//

#ifndef CS4348OS_PROJECT2_GUESTQUEUE_H
#define CS4348OS_PROJECT2_GUESTQUEUE_H
#include "Lock.h"
#include "queue"
#include "Guest.h"



class GuestQueue {
public:

    void add(Guest* input){
       Lock lock(mutex_sem); // locks queue
       guest_queue.push(input); // adds input
       queue_sem.post(); // signals saying something was added to queue
    }

    Guest* pop(){
       queue_sem.wait(); // waits for something to be added to queue
       Lock lock(mutex_sem); // locks queue
       // return
       Guest* temp = guest_queue.front();
       guest_queue.pop();
       return temp;


    }


private:
    std::queue<Guest*> guest_queue;
    Sem mutex_sem = Sem(1);
    Sem queue_sem = Sem(0);

};


#endif //CS4348OS_PROJECT2_GUESTQUEUE_H
