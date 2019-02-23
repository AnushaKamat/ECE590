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
            std::cout << "send:" << r << std::endl;
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
            loop_max_count =0;
            
        }
        void start() {
            filtered_val = 0.0;
        }
        void update() {
            
            if(channel("link").size() >= w.size()){
                loop_max_count = w.size();
            }
            else{
                loop_max_count = channel("link").size();
            }
            for(int i =0; i < loop_max_count; i++) {
                double x = channel("link").pop_earliest();
                //std::cout <<"Channel output " << "_" << i << ":" << x <<"\n";
                filtered_val +=x*w[i];
            } 
           // std::cout << "filtered:" << filtered_val << std::endl;
        }
        inline double value() { return filtered_val; }
        void stop() {}

      private:
        // add any private variable you need here
        double filtered_val;
        int loop_max_count;
        vector<double> w;
    };
}

#endif