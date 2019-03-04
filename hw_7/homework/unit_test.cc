#include "gtest/gtest.h"
#include "robot.h"
#include "stopwatch.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace elma;

double tolerance = 0.01;
/*!!
 * Here we use your StopWatch class to time something.
 */


class testClass : public Process {

    public:
    testClass() : Process("testclass") {}
    void init() {
        watch("a", [this](Event& e) {
            std::cout << "I am in AA" <<std::endl;
        },1);
        watch("a", [this](Event& e) {
            std::cout << "I am in AD" <<std::endl;
        });
        watch("a", [this](Event &e) {
            std::cout << "I am in AB" <<std::endl;
        },0);
        watch("b", [this](Event &e) {
            std::cout << "I am in BB" <<std::endl;
        },2);
        watch("a", [this](Event& e) {
            std::cout << "I am in AC" <<std::endl;
        },6);        
    }
    void start() {}
    void update() {}
    void stop() {}
};



TEST(Question1, StopWatch) {
    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    m.emit(Event("stop"));

} 
    
TEST(STOPWATCH, BASIC1){

    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    m.emit(Event("stop"));

    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.5, tolerance);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 2.0, tolerance);

    m.emit(Event("stop"));    
}  
    

   
TEST(STOPWATCH, BASIC2){

    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    m.emit(Event("stop"));
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);
    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.5, tolerance);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 2.0, tolerance);

    m.emit(Event("stop"));
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m.emit(Event("reset"));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    m.emit(Event("stop"));
            
    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    } 

    
   
TEST(STOPWATCH, BASIC3){
    
    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    m.emit(Event("reset"));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    m.emit(Event("stop"));
            
    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

} 
    
TEST(STOPWATCH, BASIC4){

    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);
    m.emit(Event("start"));
    EXPECT_NEAR(watch.seconds(), 0.0, tolerance);

    m.emit(Event("stop"));
            
    EXPECT_NEAR(watch.seconds(), 0.0, tolerance);
} 
    
TEST(STOPWATCH, BASIC5){

    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    m.emit(Event("reset"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.0, tolerance);
    m.emit(Event("stop"));
            
    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

} 


/*!!
 * Here we use your Robot class to give the robot
 * a little trial and see what state its in.
 *
 * Variants of tests will include more than one robot,
 * non-sense events, and varying event sequences.
 */

TEST(Question2, RobotEnvironment1) {

    // create a new robot
    Robot robot = Robot("What a very nice robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));


    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";

    /*
     * Send signals to robot and test
     */
    
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    EXPECT_EQ(robot.current().name(), noise.c_str());

    m.emit(Event("proximity warning"));
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("battery full"));
    EXPECT_EQ(robot.current().name(), evade.c_str());
}
TEST(Question2, RobotEnvironment2) {

    // create a new robot
    Robot robot = Robot("fully travelled robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));


    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";
    string findRS = "Find Recharge Station";
    string rec="Recharge";

    /*
     * Send signals to robot and test
     */
   
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("battery low"));
    EXPECT_EQ(robot.current().name(), findRS.c_str());

    m.emit(Event("found recharge station"));
    EXPECT_EQ(robot.current().name(), rec.c_str());

    m.emit(Event("battery full"));
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    EXPECT_EQ(robot.current().name(), noise.c_str());

    m.emit(Event("proximity warning"));
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("battery low"));
    EXPECT_EQ(robot.current().name(), findRS.c_str());
}

TEST(Question2, RobotEnvironment3) {

    // create a new robot
    //Robot robot = Robot("What a very nice robot");
    Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));
    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";
    string findRS = "Find Recharge Station";
    string rec="Recharge";
    
    /*
     * Send signals to robot and test
     */
  
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("battery low"));
    EXPECT_EQ(robot.current().name(), findRS.c_str());

    m.emit(Event("found recharge station"));
    EXPECT_EQ(robot.current().name(), rec.c_str());

    m.emit(Event("battery full"));
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    EXPECT_EQ(robot.current().name(), noise.c_str());

    m.emit(Event("proximity warning"));
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("reset"));
    EXPECT_EQ(robot.current().name(), noise.c_str());
}

TEST(Question2, RobotEnvironment4) {

    // create a new robot
    Robot robot = Robot("Dude robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));


    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";
    string findRS = "Find Recharge Station";
    string rec="Recharge";

    /*
     * Send signals to robot and test
     */

    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("stop"));
    EXPECT_EQ(robot.current().name(), wander.c_str());
}
TEST(Question2, RobotEnvironment5) {

    // create a new robot
    Robot robot = Robot("What a very nice robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));


    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";
    string findRS = "Find Recharge Station";
    string rec="Recharge";
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("proximity warning"));
    EXPECT_EQ(robot.current().name(), wander.c_str());
}

TEST(Question2, RobotEnvironment6) {

    // create a new robot
    Robot robot = Robot("What a very nice robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));


    string wander = "Wander";
    string noise = "Make Noise";
    string evade = "Evade";
    string findRS = "Find Recharge Station";
    string rec="Recharge";
    EXPECT_EQ(robot.current().name(), wander.c_str());
    m.emit(Event("reset"));
}
/*!!
 * Here we will create various StateMachines and validate the JSON from the to_json method.
 */

TEST(Question3, to_json) {
    /*
     * coming soon... but this is straight-forward to test. At this point, you shouldn't
     * need help writing tests for this one.
     */
    Robot robot = Robot("What a very nice robot");
    // Robot robot = Robot(); // << this should also work

    // init manager
    Manager m;
    
    m.schedule(robot, 10_ms)
    .init()
    .start()
    .emit(Event("start"));
    std::cout << "\n\n state machine  is :\n" << robot.to_json().dump(4) <<std::endl;
}

/*!!
 * Here we will test priority of watching events. Events with higher priority should always be
 * executed before events of lower priority.
 *
 * Test variants will include testing various events of lower and higher priority.
 */

TEST(Question4, WatchPriority) {
    /*
     * coming soon...
     */
    testClass tC;
    Manager m;

    m.schedule(tC, 10_ms)
      .init();

    m.start();
    m.emit(Event("b"));
    m.emit(Event("a"));
}
/*Test case provided by Anup on Discussion Board*/
TEST(Question4, WatchPriority2) {

 Manager m;

 vector<int> marbles;

 Stopwatch watch = Stopwatch();

 m.schedule(watch, 10_ms)

 .init();

 watch.watch("garble", [&] (Event&) {

 
 marbles.push_back(1);

 }, 1);

 watch.watch("garble", [&] (Event&) {



 marbles.push_back(10);

 }, 10);

 watch.watch("garble", [&] (Event&) {



 marbles.push_back(5);

 }, 5);

 watch.watch("garble", [&] (Event&) {



 marbles.push_back(0);

 }, 0);

 watch.watch("garble", [&] (Event&) {



 marbles.push_back(10);

 }, 10);

 watch.watch("garble", [&] (Event&) {



 marbles.push_back(1);

 }, 1);

 watch.watch("garble", [&] (Event&) {



 marbles.push_back(0);

 });

 m.emit(Event("garble"));

 EXPECT_EQ(marbles.size(), 7);

 EXPECT_EQ(marbles.at(0), 10);

 EXPECT_EQ(marbles.at(1), 10);

 EXPECT_EQ(marbles.at(2), 5);

 EXPECT_EQ(marbles.at(3), 1);

 EXPECT_EQ(marbles.at(4), 1);

 EXPECT_EQ(marbles.at(5), 0);

 EXPECT_EQ(marbles.at(6), 0);

}