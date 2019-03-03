#include "gtest/gtest.h"
#include "robot.h"
#include "stopwatch.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace elma;

double tolerance = 0.02;
/*!!
 * Here we use your StopWatch class to time something.
 */

TEST(Question1, StopWatch) {
    Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::cout << watch.seconds() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("stop"));

} 
    TEST(STOPWATCH, BASIC1){

        Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::cout << watch.seconds() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("stop"));

     m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.5, tolerance);

    std::cout << watch.seconds() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 2.0, tolerance);

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("stop"));

        
    }  
    
        TEST(STOPWATCH, BASIC2){



         Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    std::cout << watch.seconds() << std::endl;
    std::cout << "STRAT emitted" <<std::endl;
    m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::cout << watch.seconds() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("stop"));
    
std::this_thread::sleep_for(std::chrono::milliseconds(500));
EXPECT_NEAR(watch.seconds(), 1.0, tolerance);
     m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.5, tolerance);

    std::cout << watch.seconds() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 2.0, tolerance);

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("stop"));
    
std::this_thread::sleep_for(std::chrono::milliseconds(500));
m.emit(Event("reset"));
std::this_thread::sleep_for(std::chrono::milliseconds(500));
std::cout <<"After reset must be zero : "<< watch.seconds() << std::endl;
m.emit(Event("start"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

    std::cout << "starting after rest : " <<watch.seconds() << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    std::cout << watch.seconds() << std::endl;

    m.emit(Event("stop"));
            
    EXPECT_NEAR(watch.seconds(), 1.0, tolerance);

    } 
    //what should happen if start is called after start or stop is called after reset ?
    
    TEST(STOPWATCH, BASIC3){



         Manager m;

    Stopwatch watch = Stopwatch();

    m.schedule(watch, 10_ms)
    .init()
    .start();

    std::cout << watch.seconds() << std::endl;

m.emit(Event("reset"));
std::cout << watch.seconds() << std::endl;
std::this_thread::sleep_for(std::chrono::milliseconds(500));
std::cout <<"After reset must be zero : "<< watch.seconds() << std::endl;
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

    std::cout << watch.seconds() << std::endl;

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

    std::cout << watch.seconds() << std::endl;

m.emit(Event("reset"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    EXPECT_NEAR(watch.seconds(), 0.0, tolerance);
    //m.emit(Event("start"));
    //EXPECT_NEAR(watch.seconds(), 0.5, tolerance);

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
    
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), noise.c_str());

    m.emit(Event("proximity warning"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("battery full"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());
}

TEST(Question2, RobotEnvironment2) {

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

    /*
     * Send signals to robot and test
     */
    
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("battery low"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), findRS.c_str());

    m.emit(Event("found recharge station"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), rec.c_str());

    m.emit(Event("battery full"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), noise.c_str());

     m.emit(Event("proximity warning"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("battery low"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), findRS.c_str());
}

TEST(Question2, RobotEnvironment3) {

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

    /*
     * Send signals to robot and test
     */
    
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("battery low"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), findRS.c_str());

    m.emit(Event("found recharge station"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), rec.c_str());

    m.emit(Event("battery full"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("intruder detected"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), noise.c_str());

     m.emit(Event("proximity warning"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), evade.c_str());

    m.emit(Event("reset"));
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), noise.c_str());
}

TEST(Question2, RobotEnvironment4) {

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

    /*
     * Send signals to robot and test
     */
    
    std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

    m.emit(Event("stop"));
    std::cout << robot.current().name() << std::endl;
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
std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());

     m.emit(Event("proximity warning"));
    std::cout << robot.current().name() << std::endl;
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
std::cout << robot.current().name() << std::endl;
    EXPECT_EQ(robot.current().name(), wander.c_str());
    m.emit(Event("reset"));
    std::cout << robot.current().name() << std::endl;
   //StateMachine mvm = StateMachine("mnt");
   
    //robot.to_json();
   
   //std::cout << "state machine  is :\n" << exmpl.dump(3) <<std::endl;
   std::cout << "\n\n state machine  is :\n" << robot.to_json().dump(4) <<std::endl;
    //std::cout << "robot.to_json[name]" << robot.to_json()[0];
}
/*!!
 * Here we will create various StateMachines and validate the JSON from the to_json method.
 */

//TEST(Question3, to_json) {
    /*
     * coming soon... but this is straight-forward to test. At this point, you shouldn't
     * need help writing tests for this one.
     */
//}

/*!!
 * Here we will test priority of watching events. Events with higher priority should always be
 * executed before events of lower priority.
 *
 * Test variants will include testing various events of lower and higher priority.
 */
/*TEST(Question4, WatchPriority) {
    /*
     * coming soon...
     */
//}