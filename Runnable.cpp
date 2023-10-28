//
// Created by Alexander Chan-Nui on 10/28/23.
//

#include "Runnable.h"
static void *runnable_invoke(void *handle) {
   auto obj = reinterpret_cast<Runnable *>(handle);
   obj->loop();
   pthread_exit(nullptr);
   return nullptr;
}

void Runnable::start() {
   pthread_create(&ptid, NULL, runnable_invoke, this);
}