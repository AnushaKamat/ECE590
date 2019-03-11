// Backbone code for HW6_Question4

#ifndef RANDOM_FILTER_H
#define RANDOM_FILTER_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "elma.h"

using std::string;
using std::vector;
using std::rand;

namespace random_filter {
    class Random : public elma::Process {
      public: 
        // you may initialize other private data in constructor
        Random(string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {
            r = (double)rand()/RAND_MAX;
            //std::cout << "send:" << r << std::endl;
            channel("link").send(r);
        }
        void stop() {}
      private:
        // add any private variable you need here
        double r;
    };


    class Filter : public elma::Process {
      public: 
        // you may initialize other private data in constructor
        Filter(std::string name, vector<double> weight) : Process(name) {
            w = weight;
        }
        void init() {
            filtered_val =0.0;  
        }
        void start() {
            filtered_val = 0.0;
            channel("link").flush(1);
        }
        void update() {
            //std::cout <<"Channel width : " << channel("link").size() << "\n";
            if(w.size() <= 0){
                throw std::range_error("No filter parameters provided."); 
            }
            if(channel("link").size() <= w.size()){
                double x = channel("link").latest();
                filtered_val +=x*w[channel("link").size()-1];
            }
            //std::cout << "filtered:" << filtered_val << std::endl;
        }
        inline double value() { return filtered_val; }
        void stop() {}

      private:
        // add any private variable you need here
        double filtered_val;
        vector<double> w;
    };
}

#endif