//
// Created by Alexander Chan-Nui on 10/25/23.
//

#ifndef CS4348OS_PROJECT2_LOGGER_H
#define CS4348OS_PROJECT2_LOGGER_H

#include <iostream>
#include <sstream>

#include "Lock.h"


class Logger {
public:
    Logger(){}

    void print(std::string input){
       Lock lock(mutex_sem);
       std::cout << input << std::endl;
    }

    void print(std::ostringstream& input){
       Lock lock(mutex_sem);
       std::cout << input.str() << std::endl;
    }


private:
    Sem mutex_sem = Sem(1);
};


#endif //CS4348OS_PROJECT2_LOGGER_H
