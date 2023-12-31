//
// Created by Alexander Chan-Nui on 10/23/23.
//

#ifndef CS4348OS_PROJECT2_GUESTQUEUE_H
#define CS4348OS_PROJECT2_GUESTQUEUE_H

#include <queue>

#include "Lock.h"

class Guest;

class GuestQueue {
public:

    void add(Guest *input) {
       Lock lock(mutex_sem); // locks queue
       guest_queue.push(input); // adds input
       queue_sem.post(); // signals saying something was added to queue
    }

    Guest *pop() {
       queue_sem.wait(); // waits for something to be added to queue
       Lock lock(mutex_sem); // locks queue
       // return
       Guest *temp = guest_queue.front(); // gets guest from front of queue
       guest_queue.pop(); // deletes person from front
       return temp;
    }

private:
    std::queue<Guest *> guest_queue;
    Sem mutex_sem = Sem(1);
    Sem queue_sem = Sem(0);

};


#endif //CS4348OS_PROJECT2_GUESTQUEUE_H
