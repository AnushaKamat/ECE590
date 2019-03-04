#include "stopwatch.h"
#include <iostream>
/*
 * Code for Question 1 goes here
 */


void Stopwatch::init(){
    // TODO
    watch("start", [this](Event& e) {
        st = STARTED;
        _start = high_resolution_clock::now();
        _stop = _start;
        reset_flag = 0;
        });
    watch("stop", [this](Event &e) {
        st = STOPPED;
        _stop = high_resolution_clock::now();
        _dur += (_stop-_start); //duration in ns
        });
    watch("reset", [this](Event& e) {
        st = RESET;
        _start = high_resolution_clock::now();
        _stop = _start;
        _dur = high_resolution_clock::duration::zero();
        reset_flag =1 ;
        });
    _start = high_resolution_clock::now();
    _stop = _start;
    _dur = high_resolution_clock::duration::zero();//.count(); 
    this->st = INIT;
    reset_flag =1;
}

double Stopwatch::seconds(){
   
    duration<double,std::ratio<1,1>> t = high_resolution_clock::duration::zero();
   
   if(status() ==STARTED){
       t = _dur + high_resolution_clock::now() - _start;
   }
   if(status() ==STOPPED){
       t = _dur;
   }
    return t.count();
}

