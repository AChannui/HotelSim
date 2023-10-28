cmake_minimum_required(VERSION 2.8.12)
project(CS4348OS_project2)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS4348OS_project2 main.cpp Sem.h Lock.h GuestQueue.h Guest.cpp Guest.h RoomCount.h FrontDeskEmployee.cpp FrontDeskEmployee.h Logger.h Bellhop.cpp Bellhop.h Runnable.h Runnable.cpp)
add_executable(test1 test1.cpp)

target_compile_options(CS4348OS_project2 PUBLIC "-pthread" PUBLIC "-std=c++11")
target_link_libraries(CS4348OS_project2 PUBLIC "pthread")

target_compile_options(test1 PUBLIC "-pthread" PUBLIC "-std=c++11")
target_link_libraries(test1 PUBLIC "pthread")
