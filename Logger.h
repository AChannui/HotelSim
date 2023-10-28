//
// Created by Alexander Chan-Nui on 10/25/23.
//

#ifndef CS4348OS_PROJECT2_LOGGER_H
#define CS4348OS_PROJECT2_LOGGER_H

#include <iostream>
#include <sstream>

#include "Lock.h"


class Logger {
private:
    class IntermediateBuffer {
    public:
        explicit IntermediateBuffer(Logger& logger_) : buff(), logger(logger_){}
        IntermediateBuffer(IntermediateBuffer &&rhs) noexcept : buff(rhs.buff.str()), logger(rhs.logger) {}

        template<class T>
        IntermediateBuffer& operator<<(const T& input){
           buff << input;
           return *this;
        }

        IntermediateBuffer& flush(){
           logger.print(buff);
           buff.clear();
           buff.str("");
           return *this;
        }

    private:
        std::ostringstream buff;
        Logger& logger;
    };

public:
    Logger() {}


    IntermediateBuffer stream(){
       return IntermediateBuffer(*this);
    }

    // takes string and prints it out with new line at the end
    void print(std::string input) {
       Lock lock(mutex_sem);
       std::cout << input << std::endl;
    }

    void print(std::ostringstream &input) {
       Lock lock(mutex_sem);
       std::cout << input.str() << std::endl;
    }

    void add(std::string input){
       buffer.append(input);
    }

    void add(int input){
       buffer.append(std::to_string(input));
       buffer.append(" ");
    }

    void flush(){
       std::cout << buffer << std::endl;
       buffer.clear();
    }

private:
    std::string buffer;
    Sem mutex_sem = Sem(1);


};


#endif //CS4348OS_PROJECT2_LOGGER_H
