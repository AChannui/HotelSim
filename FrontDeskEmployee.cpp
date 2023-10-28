//
// Created by Alexander Chan-Nui on 10/23/23.
//

#include <string>
#include <iostream>
#include <sstream>

#include "FrontDeskEmployee.h"


FrontDeskEmployee::FrontDeskEmployee(
        int employee_id_, GuestQueue &check_in_queue_, RoomCount &room_count_, Logger &logger_) :
        employee_id(employee_id_),
        check_in_queue(check_in_queue_),
        room_count(room_count_),
        logger(logger_) {

}

static void *runnable_invoke(void *handle) {
   auto obj = reinterpret_cast<FrontDeskEmployee *>(handle);
   obj->loop();
   pthread_exit(nullptr);
   return nullptr;
}

void FrontDeskEmployee::start() {
   pthread_create(&ptid, NULL, runnable_invoke, this);
}

// main thread loop
void FrontDeskEmployee::loop() {
   (logger.stream() << "Front desk employee " << employee_id << " created").flush();
   while (true) {
      Guest *current_guest = check_in_queue.pop(); // grabs guest from queue
      current_guest->set_room_key(room_count.get_count()); // sets room numb
      current_guest->set_front_desk_helper(employee_id); // saves employee id to guest
      (logger.stream() <<
                "Front desk employee " << employee_id << " registers guest "
                << current_guest->get_guest_id() << " and assigns room "
                << current_guest->get_room_numb()).flush();
      current_guest->signal_room_key(); // signals guest its finished
   }
}
