#include "gtest/gtest.h"

#include <string>
#include <iostream>
#include <ratio>
#include <thread>
#include <vector>
#include <chrono>

#include "stopwatch.h"
#include "elma.h"
#include "random_filter.h"

#define SLEEP(__ms__) std::this_thread::sleep_for(std::chrono::milliseconds(__ms__))
#define MS(__ms__) high_resolution_clock::duration(milliseconds(__ms__))

using std::vector;
using std::string;
using namespace random_filter;

namespace {

    TEST(STOPWATCH, BASIC1){
        Stopwatch w;
        //std::cout << "status : "<<w.status()<<std::endl;
        w.start();
        SLEEP(100);
        w.stop();    
        SLEEP(100);
        w.start();
        SLEEP(50);
        w.stop();   
        EXPECT_NEAR(w.get_minutes(), 0.0025, 0.0008);
        EXPECT_NEAR(w.get_seconds(), 0.15, 0.05);
        EXPECT_NEAR(w.get_milliseconds(), 150, 50);
        EXPECT_NEAR(w.get_nanoseconds(), 150000000, 50000000); 

    }  
        TEST(STOPWATCH, BASIC2){
        Stopwatch w;
        w.start();
        SLEEP(200);
        w.stop();
        EXPECT_NEAR(w.get_milliseconds(), 200, 10);      
        SLEEP(200);
        EXPECT_NEAR(w.get_milliseconds(), 200, 10);   
        w.start();
        SLEEP(150);
        w.stop();  
        EXPECT_NEAR(w.get_milliseconds(), 350, 50);
        EXPECT_NEAR(w.get_minutes(), 0.00583, 0.005);
        EXPECT_NEAR(w.get_seconds(), 0.35, 0.05);
        EXPECT_NEAR(w.get_nanoseconds(), 350000000, 50000000); 
        w.reset();
        EXPECT_ANY_THROW(w.get_milliseconds());
        w.start();
        SLEEP(50);
        w.stop();
        SLEEP(50);
        EXPECT_NEAR(w.get_milliseconds(), 50, 10);

    } 
    TEST(STOPWATCH, BASICerror1){
        Stopwatch w;
        w.start();
        SLEEP(100);
        EXPECT_ANY_THROW(w.get_milliseconds());
        w.stop();  
        EXPECT_NEAR(w.get_milliseconds(), 130, 50);    
        SLEEP(100);
        w.reset();
        SLEEP(100);
        EXPECT_ANY_THROW(w.get_minutes());
        w.stop(); 
        SLEEP(100);
        EXPECT_NEAR(w.get_milliseconds(), 100, 50); 
    }  
    
    TEST(STOPWATCH, BASIC_error2){
        Stopwatch w;
        EXPECT_ANY_THROW(w.reset());
        w.start();
        SLEEP(100);
        EXPECT_ANY_THROW(w.start());
        w.stop();  
         
        SLEEP(100);
        
        w.reset();
        SLEEP(100);
        w.stop();  
         
        SLEEP(100);
        EXPECT_NEAR(w.get_milliseconds(), 100, 10);
        
    }
    class Sender : public elma::Process {
      public: 
        Sender(string name, vector<double> vect) : Process(name), _data(vect.begin(), vect.end()), _idx(0) {}
        void init() {}
        void start() {}
        void update() {
            channel("Data").send(_data[_idx++]);
            if(_idx==_data.size()) _idx=0;
        }
        void stop() {}
      private:
        int _idx;
        vector<double> _data;
    };

    class Receiver : public elma::Process {
      public: 
        Receiver(std::string name, int n) : Process(name), _sum(0.0), _n(n) {}
        void init() {}
        void start() {}
        void update() {
            if(channel("Data").nonempty()){
                _sum = 0;
                vector<double> data = channel("Data").latest(_n);
                for(auto x: data)
                    _sum += x;
            }
        }
        inline double sum() {return _sum;}
        void stop() {}
      private:
        int _n;
        double _sum;
    };
    
    TEST(LATEST, BASIC){
        vector<double> ans{1, 3, 6, 10, 15, 21, 28, 36, 45, 55};
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        Receiver receiver("receiver", 10);
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .schedule(receiver, MS(10))
        .add_channel(data)
        .init();
        for(int i=0; i<ans.size(); i++){
            m.run(MS(20));
            EXPECT_DOUBLE_EQ(receiver.sum(), ans[i]);
        }
    }


    

    TEST(LATEST, BASIC2){
        vector<double> ans{1, 3, 6, 10, 15, 20, 25, 30, 35, 40};
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        Receiver receiver("receiver", 5);
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .schedule(receiver, MS(10))
        .add_channel(data)
        .init();
        for(int i=0; i<ans.size(); i++){
            m.run(MS(20));
            EXPECT_DOUBLE_EQ(receiver.sum(), ans[i]);
        }
    }

    TEST(CAPACITY, BASIC){
        elma::Manager m;
        Sender sender("sender", vector<double>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        elma::Channel data("Data");

        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(110))
        .stop();
        EXPECT_EQ(m.channel("Data").size(),10);
        //std::cout <<"Channel Capacity :" <<m.channel("Data").capacity() <<" Channel size : "<<m.channel("Data").size();
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 1);
        m.channel("Data").change_capacity(5);
        //std::cout <<"Channel Capacity :" <<m.channel("Data").capacity() <<" Channel size : "<<m.channel("Data").size();
        
        EXPECT_EQ(m.channel("Data").size(),5);
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 6);
        EXPECT_EQ(m.channel("Data").capacity(), 5);
    }
        TEST(CAPACITY, BASIC2){
        elma::Manager m;
        Sender sender("sender", vector<double>{11, 21, 31, 41, 51, 61, 71, 81, 91,98,99});
        elma::Channel data("Data");
        //EXPECT_EQ(m.channel("Data").size(),11);
        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(120))
        .stop();
        EXPECT_EQ(m.channel("Data").size(),11);
        //std::cout <<"Channel Capacity :" <<m.channel("Data").capacity() <<" Channel size : "<<m.channel("Data").size();
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 11);
        EXPECT_DOUBLE_EQ(m.channel("Data").latest(), 99);
        m.channel("Data").change_capacity(7);
        //std::cout <<"Channel Capacity :" <<m.channel("Data").capacity() <<" Channel size : "<<m.channel("Data").size();
        EXPECT_DOUBLE_EQ(m.channel("Data").latest(), 99);
        EXPECT_EQ(m.channel("Data").size(),7);
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 51);
        EXPECT_EQ(m.channel("Data").capacity(), 7);
    }
            TEST(CAPACITY, BASIC3){
        elma::Manager m;
        Sender sender("sender", vector<double>{101, 201, 301, 401, 501, 601, 701, 801, 901,908});
        elma::Channel data("Data");
        //EXPECT_EQ(m.channel("Data").size(),11);
        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(110))
        .stop();
        EXPECT_EQ(m.channel("Data").size(),10);
        //std::cout <<"Channel Capacity :" <<m.channel("Data").capacity() <<" Channel size : "<<m.channel("Data").size();
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 101);
        EXPECT_DOUBLE_EQ(m.channel("Data").latest(), 908);
        m.channel("Data").change_capacity(12);
        //std::cout <<"Channel Capacity :" <<m.channel("Data").capacity() <<" Channel size : "<<m.channel("Data").size();
        EXPECT_DOUBLE_EQ(m.channel("Data").latest(), 908);
        EXPECT_EQ(m.channel("Data").size(),10);
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 101);
        EXPECT_EQ(m.channel("Data").capacity(), 12);
    }
                TEST(CAPACITY, BASIC4){
        elma::Manager m;
        Sender sender("sender", vector<double>{10.1, 20.1, 30.1, 40.1, 50.1, 60.1, 70.1, 80.1, 90.1,90.8});
        elma::Channel data("Data");
        //EXPECT_EQ(m.channel("Data").size(),11);
        m.schedule(sender, MS(10))
        .add_channel(data)
        .init()
        .run(MS(110))
        .stop();
        EXPECT_EQ(m.channel("Data").size(),10);
        //std::cout <<"Channel Capacity :" <<m.channel("Data").capacity() <<" Channel size : "<<m.channel("Data").size();
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 10.1);
        EXPECT_DOUBLE_EQ(m.channel("Data").latest(), 90.8);
        m.channel("Data").change_capacity(120);
        //std::cout <<"Channel Capacity :" <<m.channel("Data").capacity() <<" Channel size : "<<m.channel("Data").size();
        EXPECT_DOUBLE_EQ(m.channel("Data").latest(), 90.8);
        EXPECT_EQ(m.channel("Data").size(),10);
        EXPECT_DOUBLE_EQ(m.channel("Data").earliest(), 10.1);
        EXPECT_EQ(m.channel("Data").capacity(), 120);
    }

    TEST(RANDOM_FILTER, BASIC){
        srand (0);
        elma::Manager m;
        Random r("random numbers");
        Filter f("filter", vector<double>{1, 1, 1});
        elma::Channel data("link");

        m.schedule(r, MS(10))
        .schedule(f, MS(10))
        .add_channel(data)
        .init();
       
        m.run(MS(40)).stop();
        //std::cout << "filtered value " << f.value();
        EXPECT_NEAR(f.value(),  2.01767, 0.01);
        m.run(MS(40)).stop();
        EXPECT_NEAR(f.value(),  1.90764, 0.01);
    }

    TEST(RANDOM_FILTER, BASIC2){
        srand (0);
        elma::Manager m;
        Random r("random numbers");
        Filter f("filter", vector<double>{0.1,0.1, 0.1});
        elma::Channel data("link");

        m.schedule(r, MS(10))
        .schedule(f, MS(10))
        .add_channel(data)
        .init();
       
        m.run(MS(40)).stop();
        //std::cout << "filtered value " << f.value();
        EXPECT_NEAR(f.value(),  0.201767, 0.01);
        m.run(MS(40)).stop();
        EXPECT_NEAR(f.value(),  0.190764, 0.01);
    }

        TEST(RANDOM_FILTER, BASIC3){
        srand (1);
        elma::Manager m;
        Random r("random numbers");
        Filter f("filter", vector<double>{1,1});
        elma::Channel data("link");

        m.schedule(r, MS(10))
        .schedule(f, MS(10))
        .add_channel(data)
        .init();
       
        m.run(MS(40)).stop();
        //std::cout << "filtered value " << f.value();
        EXPECT_NEAR(f.value(),  1.2345, 0.01);
        m.run(MS(40)).stop();
        EXPECT_NEAR(f.value(),  1.71001, 0.01);
    }

    class  Tester: public elma::Process {
      public: 
        Tester(string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {}
        void stop() {}
    };

    typedef std::map<string, std::tuple<string, double, double, int>> info_type;
    void ps_test( info_type& info,  info_type& ans){
        //std::cout.precision(3);
        //std::cout<<"======================================="<<std::endl;
        for(auto x: ans){
            string key = x.first;
            EXPECT_EQ(std::get<0>(info[key]), std::get<0>(x.second));
            EXPECT_NEAR(std::get<1>(info[key]), std::get<1>(x.second), 10.0);
            EXPECT_NEAR(std::get<2>(info[key]), std::get<2>(x.second), 10.0);
            EXPECT_NEAR(std::get<3>(info[key]), std::get<3>(x.second), 1);
            
            //std::cout<<key<<" || "
            //         <<std::get<0>(info[key])<<" || "
            //         <<std::get<1>(info[key])<<" || "
            //         <<std::get<2>(info[key])<<" || "
            //         <<std::get<3>(info[key])<<std::endl;
        }
        //std::cout<<"======================================="<<std::endl;
    }

    TEST(PS, BASIC){
        elma::Manager m;
        Tester james("james");
        Tester lily("lily");

        m.schedule(james, MS(17))
        .schedule(lily, MS(31));

        std::map<string, std::tuple<string, double, double, int>> ans({
            {"james", std::make_tuple("STOPPED", 85.0, 17.0, 5)},
            {"lily", std::make_tuple("STOPPED", 93.0, 31.0, 3)},
        });
        
        m.init().run(MS(100));
        auto info = m.ps();
        ps_test(info, ans);
    }

}
