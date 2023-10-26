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

static void *runnable_invoke(void *handle) {
   auto obj = reinterpret_cast<Bellhop *>(handle);
   obj->loop();
   pthread_exit(nullptr);
   return nullptr;
}

void Bellhop::start() {
   pthread_create(&ptid, NULL, runnable_invoke, this);
}

void Bellhop::loop() {
   {
      std::ostringstream stream;
      stream << "Bellhop created " << employee_id << " created";
      logger.print(stream.str());
   }
   while(true){
      Guest* current_guest = bellhop_queue.pop();
      {
         std::ostringstream stream;
         stream << "Bellhop " << employee_id << " receives bags from guest " << current_guest->get_guest_id();
         logger.print(stream.str());
      }
      current_guest->bellhop_help(this);
      current_guest->signal_bag();
      guest_sem.wait();
      {
         std::ostringstream stream;
         stream << "Bellhop " << employee_id << " delivers bags to guest " << current_guest->get_guest_id();
         logger.print(stream.str());
      }
      current_guest->signal_bag();
      guest_sem.wait();
   }
}


