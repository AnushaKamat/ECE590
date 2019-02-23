#include <iostream>
#include <stdexcept>
#include "elma.h"

namespace elma {
    
    Channel& Channel::send(double value) {
        _queue.push_front(value);
        while ( _queue.size() >= capacity() ) {
            _queue.pop_back();
        }
        return *this;
    }

    Channel& Channel::flush(double) {
        _queue.clear();
        return *this;
    }

    double Channel::latest() {
        if ( _queue.size() == 0 ) {
            throw std::range_error("Tried to get the latest value in an empty channel.");
        }
        return _queue.front();
    }

    vector<double> Channel::latest(int n){
        vector<double> result;
        // TODO: Question 2
        if(_queue.size()<n){
            n = _queue.size();
        }
        for(int i = 0; i< n ; i++){
            result.push_back(_queue[i]);
        }
        return result;
    }

    double Channel::earliest() {
        if ( _queue.size() == 0 ) {
            throw std::range_error("Tried to get the earliest value in an empty channel.");
        }
        return _queue.back();        
    }    

    double Channel::pop_earliest(){
        double x = this->earliest();
        if(_queue.size()>0){
            _queue.pop_back();
        }
        return x;
    }

    void Channel::change_capacity(int n){
        // TODO: Question 3
        /* 2 cases can occur
         * case 1: new capacity n is more than old capacity
         *          then simply increase the capacity
         * case 2 : new cap is less than old 
         *              then flush out extra
         */
        if(n <= 0){
            throw std::range_error("Capacity cannot be 0 or negative");
        }
        
        if(_queue.size()>n){ 
                  
            for(int i = _queue.size()-n ; i > 0 ; i--){
                _queue.pop_back();
            }
        }
        _capacity = n;
        
    }
}