#include <iostream>
#include <random>

#include "Bellhop.h"
#include "Guest.h"
#include "FrontDeskEmployee.h"


int main() {
   std::cout << "Hello, World!" << std::endl;
   srand(time(NULL));
   int guest_list_size = 25;
   int front_desk_size = 2;
   int bellhop_list_size = 2;
   int exit_count = 0;
   GuestQueue front_desk_queue;
   GuestQueue bellhop_queue;
   GuestQueue exit_queue;
   RoomCount room_count;
   Logger logger;


   // creation of front desk employees
   std::vector<FrontDeskEmployee> front_desk;
   for (int i = 0; i < front_desk_size; i++) {
      front_desk.push_back(FrontDeskEmployee(i, front_desk_queue, room_count, logger));
   }

   // start front desk employees
   for (auto &frontDeskEmployee: front_desk) {
      frontDeskEmployee.start();
   }

   // creation of bellhops
   std::vector<Bellhop> bellhop_list;
   for(int i = 0; i < bellhop_list_size; i++){
      pthread_t ptid;
      bellhop_list.push_back(Bellhop(i, bellhop_queue, logger));
   }

   // start of bellhops
   for(auto &bellhop : bellhop_list){
      bellhop.start();
   }

   // creations of guests
   std::vector<Guest> guest_list;
   for (int i = 0; i < guest_list_size; i++) {
      int bag_count = rand() % 6;
      pthread_t ptid;
      guest_list.push_back(
              Guest(i, bag_count, front_desk_queue, bellhop_queue, exit_queue, logger));
   }

   // start guests
   for (auto &guest: guest_list) {
      guest.start();
   }




   while (exit_count < guest_list_size) {
      Guest *current_guest = exit_queue.pop();
      pthread_join(current_guest->get_ptid(), nullptr);
      {
         std::ostringstream stream;
         stream <<  "Guest " << current_guest->get_guest_id() << " joined";
         logger.print(stream.str());
      }
      exit_count++;
   }

   return 0;
}
