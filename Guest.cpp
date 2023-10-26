//
// Created by Alexander Chan-Nui on 10/23/23.
//

#include "Bellhop.h"
#include "Guest.h"


// constructor with initialization for local vars
Guest::Guest(int guest_numb_, int bag_numb_, GuestQueue &check_in_queue_,
             GuestQueue &bellhop_queue_, GuestQueue &exit_queue_, Logger &logger_) :
        guest_id(guest_numb_),
        bag_numb(bag_numb_),
        check_in_queue(check_in_queue_),
        bellhop_queue(bellhop_queue_),
        exit_queue(exit_queue_),
        logger(logger_),
        bag_limit(2) {}

static void *runnable_invoke(void *handle) {
   auto obj = reinterpret_cast<Guest *>(handle);
   obj->loop();
   pthread_exit(nullptr);
   return nullptr;
}

// creates thread
void Guest::start() {
   pthread_create(&ptid, NULL, runnable_invoke, this);
}

// main thread actions
void Guest::loop() {
   // creation print
   {
      std::ostringstream stream;
      stream << "Guest " << guest_id << " created";
      logger.print(stream.str());
   }

   // entering hotel print
   {
      std::ostringstream stream;
      stream << "Guest " << guest_id << " enters hotel with " << bag_numb << " bags";
      logger.print(stream.str());
   }


   check_in_queue.add(this); // adds self to check in queue
   room_key_sem.wait(); // waits for a front desks employee's help

   // get room key print
   {
      std::ostringstream stream;
      stream << "Guest " << guest_id << " receives room key for room " << room_numb
             << " from front desk employee " << front_desk_helper;
      logger.print(stream.str());
   }

   // getting a bellhop if bags are above set amount
   if (bag_numb > bag_limit) {
      // waiting for bellhop print
      {
         std::ostringstream stream;
         stream << "Guest " << guest_id << " requests help with bags";
         logger.print(stream.str());
      }
      bellhop_queue.add(this); // adds self to bellhop queue
      bag_sem.wait(); // waits for bellhop help
   }

   {
      std::ostringstream stream;
      stream << "Guest " << guest_id << " enters room " << room_numb;
      logger.print(stream.str());
   }

   if (bag_numb > bag_limit) {
      bellhop->guest_signal(); // signals bellhop guest has entered room
      bag_sem.wait(); // guest waits for bags
      {
         std::ostringstream stream;
         stream << "Guest " << guest_id << " receives bags from bellhop "
                << bellhop->get_employee_id() << " and gives tip";
         logger.print(stream.str());
      }
      bellhop->guest_signal(); // signals bellhop for tip
   }


   {
      std::ostringstream stream;
      stream << "Guest " << guest_id << " retires for the evening";
      logger.print(stream.str());
   }

   exit_queue.add(this); // adds self to exit queue for join
   pthread_exit(nullptr); // exits thread

}