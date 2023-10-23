cmake_minimum_required(VERSION 3.24)
project(CS4348OS_project2)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS4348OS_project2 main.cpp Sem.h Lock.h GuestQueue.h Guest.cpp Guest.h RoomCount.h)
