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
        });
    watch("stop", [this](Event &e) {
        if(st == STARTED){
        st = STOPPED;
        _dur += high_resolution_clock::now()-_start; //duration in ns
        }
        });
    watch("reset", [this](Event& e) {
        st = STOPPED;
        _dur = high_resolution_clock::duration::zero();
        });
    
    st = STOPPED;
    _dur = high_resolution_clock::duration::zero();
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

