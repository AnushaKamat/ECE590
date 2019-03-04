#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <chrono>
#include "elma.h"
#include <chrono>

using namespace elma;
using namespace std::chrono;
typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;

class Stopwatch : public elma::Process {
    public: 
        Stopwatch():Process("stopwatch"){}
        void init();
        void start(){}
        void update(){}
        void stop(){}
        
        double seconds();
        inline int status() {return st;}
        typedef enum { STARTED, STOPPED } statusType;

    private:
    high_resolution_clock::time_point _start;
    high_resolution_clock::duration _dur; 
    statusType st;
    
};

#endif