#include "stopwatch.h"
#include <iostream>

void Stopwatch::start(){
    if(_status==STOPPED){
        _start_time = high_resolution_clock::now();
        _status = RUNNING;
    }
}

void Stopwatch::stop(){
    if(_status==RUNNING){
        _elapsed += high_resolution_clock::now() - _start_time;
        _status = STOPPED;
    }
}

void Stopwatch::reset(){
    _elapsed = high_resolution_clock::duration::zero();
    _status = STOPPED;
}

double Stopwatch::get_minutes(){
    if(_status==RUNNING)
        return minutes_type(_elapsed + high_resolution_clock::now() - _start_time).count();
    else
        return minutes_type(_elapsed).count();
}
double Stopwatch::get_seconds(){
    if(_status==RUNNING)
        return minutes_type(_elapsed + high_resolution_clock::now() - _start_time).count();
    else
        return seconds_type(_elapsed).count();
}
double Stopwatch::get_milliseconds(){
    if(_status==RUNNING)
        return minutes_type(_elapsed + high_resolution_clock::now() - _start_time).count();
    else
        return milliseconds_type(_elapsed).count();
}
double Stopwatch::get_nanoseconds(){
    if(_status==RUNNING)
        return minutes_type(_elapsed + high_resolution_clock::now() - _start_time).count();
    else
        return nanoseconds_type(_elapsed).count();
}
