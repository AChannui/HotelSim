//
// Created by Alexander Chan-Nui on 10/25/23.
//

#include "Bellhop.h"
#include "Guest.h"


Bellhop::Bellhop(int employee_id_, GuestQueue &bellhop_queue_, Logger &logger_) :
        employee_id(employee_id_),
        bellhop_queue(bellhop_queue_),
        logger(logger_),
        mutex_sem(Sem(1)),
        guest_sem(Sem(0)) {
}


// main loop
void Bellhop::loop() {
   // creation print message
   (logger.stream() << "Bellhop created " << employee_id << " created").flush();
   // main loop
   while (true) {
      Guest *current_guest = bellhop_queue.pop(); // waits and grabs next guest in queue
      (logger.stream() << "Bellhop " << employee_id << " receives bags from guest "
                << current_guest->get_guest_id()).flush();
      current_guest->bellhop_help(this); // gives pointer to self to the guest its helping
      current_guest->signal_bag(); // signalling guest the bellhop took their bags
      guest_sem.wait(); // waits for guest to get to room
      (logger.stream() << "Bellhop " << employee_id << " delivers bags to guest "
                << current_guest->get_guest_id()).flush();
      current_guest->signal_bag(); // signals guest they gave bags back
      guest_sem.wait(); // waits for tip
   }
}


