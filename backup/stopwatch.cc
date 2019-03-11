// Backbone code for HW6_Question1
#include "stopwatch.h"
#include <iostream>

Stopwatch::Stopwatch(){
    // TODO
    _start = high_resolution_clock::now();
    _stop = _start;
    _dur = high_resolution_clock::duration::zero();//.count(); 
    this->st = INIT;
}

void Stopwatch::start(){
    // TODO
    //std::cout <<"Inside start: "<<status()<<std::endl;
    if(status() == 1){
        throw std::invalid_argument("Cannot again start as Stopwatch is already started") ;
    }
    _start = high_resolution_clock::now();
    _stop = _start;
    this->st = STARTED;
}

void Stopwatch::stop(){
    // TODO
    //std::cout <<"Inside : "<<status()<<std::endl;
    if(!(status() == 1 || status() == 3)){
        throw std::invalid_argument("Cannot stop a Stopwatch when not started") ;
    }
    _stop = high_resolution_clock::now();
    _dur += (_stop-_start); //duration in ns
    this->st=STOPPED;
    //std::cout << _dur.count();
}

void Stopwatch::reset(){
    if(!(status() == 2)){
        throw std::invalid_argument("Cannot reset a Stopwatch when not stopped") ;
    }
    _start = high_resolution_clock::now();
    _stop = _start;
    _dur = high_resolution_clock::duration::zero();
    this->st = RESET;
}

double Stopwatch::get_minutes(){
    if(status() != 2){
        throw std::invalid_argument("Cannot provide time if Stopwatch is not stopped") ;
    }
    duration<double,std::ratio<60>> t = _dur;
    return t.count();   
}
double Stopwatch::get_seconds(){
    if(status() != 2){
        throw std::invalid_argument("Cannot provide time if Stopwatch is not stopped") ;
    }
    duration<double,std::ratio<1,1>> t = _dur;
    return t.count();
}
double Stopwatch::get_milliseconds(){
    if(status() != 2){
        throw std::invalid_argument("Cannot provide time if Stopwatch is not stopped") ;
    }
    duration<double,std::milli> t = _dur;
    return t.count();
}
double Stopwatch::get_nanoseconds(){
    if(status() != 2){
        throw std::invalid_argument("Cannot provide time if Stopwatch is not stopped") ;
    }
    return _dur.count();
}

