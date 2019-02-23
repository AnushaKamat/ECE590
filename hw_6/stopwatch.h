// Backbone code for HW6_Question1

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

using namespace std::chrono;
typedef enum { INIT, STARTED, STOPPED } statusType;
class Stopwatch{
    public:
        Stopwatch();
        void start();              // starts the timer
        void stop();               // stops the timer
        void reset();              // sets stopwatch to zero
        
        //statusType status();
        double get_minutes();      // number of minutes counted
        double get_seconds();      // number of seconds counted
        double get_milliseconds(); // number of milliseconds counted
        double get_nanoseconds();  // number of nanoseconds counted
        statusType st;
    private:
       high_resolution_clock::time_point _start,_stop;
       high_resolution_clock::duration _dur; // declare any private variable you need here, we won't access them since they are private
       
       
};

#endif