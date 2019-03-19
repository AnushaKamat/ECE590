#ifndef RANDOM_FILTER_H
#define RANDOM_FILTER_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "elma.h"
//Random Filter for data coming through the channel
using std::string;
using std::vector;

namespace random_filter {
    class Random : public elma::Process {
      public: 
        Random(string name) : Process(name), _idx(0.0) {}
        void init() {}
        void start() {}
        void update() {
            double val = (double)rand() / RAND_MAX;
            channel("link").send(val);
            std::cout<<"send: "<<val<<"\n";
        }
        void stop() {}
      private:
        int _idx;
    };


    class Filter : public elma::Process {
      public: 
        Filter(std::string name, vector<double> vect) : Process(name), _weight(vect.begin(), vect.end()), _value(0) {}
        void init() {
            if(_weight.size()>channel("link").capacity()){
                channel("link").change_capacity(_weight.size()*2);
            }
        }
        void start() {
            ///for(auto x: _weight)
            //    std::cout<<x<<" ";
            //std::cout<<std::endl;
        }
        void update() {
            if(channel("link").nonempty()){
                _value = 0;
                vector<double> data = channel("link").latest(_weight.size());
                for(int i=0; i<data.size(); i++){
                    _value += data[i] * _weight[i];
                    std::cout<<data[i]<<" "<<_weight[i]<<std::endl;
                }
                std::cout<<"value: "<<_value<<std::endl;;
            }
        }
        inline double value() {return _value;}
        void stop() {}
      private:
        double _value;
        vector<double> _weight;
    };
}

#endif