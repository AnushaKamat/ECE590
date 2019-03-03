#include <iostream>
#include <chrono>
#include "elma.h"

using namespace elma;

/*!
 * This is an internally used by Robot. We won't be testing this class.
 */
class RobotState : public State {

    /*
     * Question 2: define a 'RobotState' that inherits from 'State'
     * Hint 1: you'll need to implement the 'virtual' methods and inherit both of
     * the 'State' constructors.
     */
    public:

        //! Construct an unnamed State
        RobotState():State() {}
        //! Construct a state with the given name
        RobotState(std::string name):State(name) {}
        void entry(const Event& e) {}
        void during() {} 
        void exit(const Event& e) {}


};

class Robot : public StateMachine {
public:
    /*
     * Implement contructors. Constructors should instantiate states
     * and transitions AND should set initial_state so that Event('start')
     * sets the Robot to state 'Wander'
     *
     * Look at code for StateMachine.h and in examples and elma/example if you need help.
     *
     * States should have the EXACT names:
     * "Recharge"
     * "Wander"
     * "Find Recharge Station"
     * "Evade"
     * Make Noise"
     *
     * Robot should respond to events with the EXACT names:
     * "found recharge station"
     * "battery full"
     * "battery low"
     * "start"
     * "reset"
     * "intruder detected"
     * "proximity warning"
     */
        Robot():StateMachine() {
            Robot robot = Robot("Robot name unknown");
        }
        //! Construct a state with the given name
        Robot(std::string name):StateMachine(name) {
            idle = RobotState("Idle");
            recharge =  RobotState("Recharge");
            wander =  RobotState("Wander");
            findRechargeStation =  RobotState("Find Recharge Station");
            evade =  RobotState("Evade");
            makeNoise =  RobotState("Make Noise");
            this
                ->set_initial(idle)
                .add_transition("start", idle, wander)
                .add_transition("battery low", wander, findRechargeStation)
                .add_transition("found recharge station", findRechargeStation, recharge)

                .add_transition("battery full", recharge, wander)
                .add_transition("reset", makeNoise, wander)

                .add_transition("intruder detected", wander, makeNoise)
                .add_transition("proximity warning", makeNoise, evade)
                .add_transition("reset", evade, makeNoise)
                .add_transition("battery low", evade, findRechargeStation);

        }
        







private:
    /*
     * Hint: You may want to keep RobotState here since locally declared variables are destroyed
     */
    RobotState idle;
    RobotState recharge;
    RobotState wander;
    RobotState findRechargeStation;
    RobotState evade;
    RobotState makeNoise;
    

};