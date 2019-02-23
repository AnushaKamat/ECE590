// Backbone code for HW6_Question1
#include "stopwatch.h"
#include <iostream>

Stopwatch::Stopwatch(){
    // TODO
    _start = high_resolution_clock::now();
    _stop = _start;
    _dur = high_resolution_clock::duration::zero();//.count(); 
    st = INIT;
}

void Stopwatch::start(){
    // TODO
    _start = high_resolution_clock::now();
    _stop = _start;
    st = STARTED;
}

void Stopwatch::stop(){
    // TODO
    _stop = high_resolution_clock::now();
    _dur += (_stop-_start); //duration in ns
    st=STOPPED;
    std::cout << _dur.count();
}

void Stopwatch::reset(){
    _start = high_resolution_clock::now();
    _stop = _start;
    _dur = high_resolution_clock::duration::zero();
    st = INIT;
}

double Stopwatch::get_minutes(){
    duration<double,std::ratio<60>> t = _dur;
    return t.count();   
}
double Stopwatch::get_seconds(){
    duration<double,std::ratio<1,1>> t = _dur;
    return t.count();
}
double Stopwatch::get_milliseconds(){
    duration<double,std::milli> t = _dur;
    return t.count();
}
double Stopwatch::get_nanoseconds(){
    return _dur.count();
}

