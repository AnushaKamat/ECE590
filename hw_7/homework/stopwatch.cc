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

void Stopwatch::start(){

    /*
    // TODO
    //std::cout <<"Inside start: "<<status()<<std::endl;
    if ( e.name() == "start" ) {
        emit(Event("set power", e.value()));
        if(status() == 1){
            throw std::invalid_argument("Cannot again start as Stopwatch is already started") ;
        }
        _start = high_resolution_clock::now();
        _stop = _start;
        this->st = STARTED;
    }
    */
    
}

void Stopwatch::stop(){
    /*
    // TODO
    //std::cout <<"Inside : "<<status()<<std::endl;
    if ( e.name() == "stop" ) {
    if(!(status() == 1 || status() == 3)){
        throw std::invalid_argument("Cannot stop a Stopwatch when not started") ;
    }
    _stop = high_resolution_clock::now();
    _dur += (_stop-_start); //duration in ns
    this->st=STOPPED;
    //std::cout << _dur.count();
    }
    */
}



void Stopwatch::update(){
/*
    if ( e.name() == "reset" ) {
    if(!(status() == 1)){
        throw std::invalid_argument("Cannot reset a Stopwatch when not stopped") ;
    }
    _start = high_resolution_clock::now();
    _stop = _start;
    _dur = high_resolution_clock::duration::zero();
    this->st = RESET;
    }
    */
   if ( st == STARTED ) {
        _start = high_resolution_clock::now();
        _stop = _start;
        reset_flag = 0;
        std::cout <<"reset_flag is unset in start : " <<reset_flag <<std::endl;
        this->st = INIT;
    }
    if ( st == STOPPED ) {
      _stop = high_resolution_clock::now();
    _dur += (_stop-_start); //duration in ns
    this->st=INIT;
    }
    if ( st == RESET ) {
    _start = high_resolution_clock::now();
    _stop = _start;
    _dur = high_resolution_clock::duration::zero();
    reset_flag =1 ;
    
    this->st = INIT;
    }
   
}
double Stopwatch::seconds(){
    /*
    if(status() == 0){
        throw std::invalid_argument("Cannot provide time if Stopwatch is not started") ;
    }
    */
   
    duration<double,std::ratio<1,1>> t = high_resolution_clock::duration::zero();
   
   if(status() ==STARTED){
       t = _dur + high_resolution_clock::now() - _start;
   }
   if(status() ==STOPPED){
       t = _dur;
   }
    return t.count();
}

