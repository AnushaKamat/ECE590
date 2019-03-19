#ifndef STOPWATCH_H
#define STOPWATCH_H
//Stopwatch class
#include <chrono>

typedef std::chrono::duration<double, std::ratio<60,1>> minutes_type;
typedef std::chrono::duration<double, std::ratio<1,1>> seconds_type;
typedef std::chrono::duration<double, std::milli> milliseconds_type;
typedef std::chrono::duration<double, std::nano> nanoseconds_type;


using namespace std::chrono;


class Stopwatch{
    public:
        typedef enum {STOPPED, RUNNING } status_type;
        Stopwatch(): _status(STOPPED), _elapsed(high_resolution_clock::duration::zero()) {}
        void start();              // starts the timer
        void stop();               // stops the timer
        void reset();              // sets stopwatch to zero

        double get_minutes();      // number of minutes counted
        double get_seconds();      // number of seconds counted
        double get_milliseconds(); // number of milliseconds counted
        double get_nanoseconds();  // number of nanoseconds counted
    private:
        status_type _status;
        high_resolution_clock::duration _elapsed;
        high_resolution_clock::time_point _start_time;
};

#endif