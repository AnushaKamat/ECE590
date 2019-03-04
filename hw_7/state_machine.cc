#include <iostream>
#include "elma.h"

namespace elma {

    int State::_id_counter = 0;

    StateMachine& StateMachine::set_initial(State& s) {
        _initial = &s;
        return *this;
    }

    StateMachine& StateMachine::add_transition(string event_name, State& from, State& to) {
        _transitions.push_back(Transition(event_name, from, to));
        to._state_machine_ptr = this;
        from._state_machine_ptr = this;
        return *this;
    }

    void StateMachine::init() {
        for (auto transition : _transitions ) {
            watch(transition.event_name(), [this, transition](Event& e) {
                if ( _current->id() == transition.from().id() ) {
                    _current->exit(e);
                    _current = &transition.to();
                    _current->entry(e);
                    if ( !_propagate ) {
                      e.stop_propagation();
                    }
                }
            });
        }
    }

    void StateMachine::start() {
        if ( _initial == NULL ) { 
            throw(Exception("State machine started without an initial state (call set_initial(...) first)"));
        }
        _current = _initial;
        _current->entry(Event("start"));
    }

    void StateMachine::update() {
        _current->during();
    }

    void StateMachine::stop() {}

    json StateMachine::to_json(){
        json transitions = {};
        std::set<string> states;
        for(int i = 0; i < _transitions.size();i++){
            string from_state = _transitions[i].from().name();
            string to_state = _transitions[i].to().name();
            string when = _transitions[i].event_name();
            
            states.insert(from_state);
            states.insert(to_state);

            json::object_t tr = {   
                                    {"from", from_state},
                                    {"to",to_state},
                                    {"when",when}
                                };
            json tr_json(tr);
            transitions.push_back(tr_json);
        }
        json::object_t sm_t = {{"name",  this->name()}, {"states", states}, {"transitions",transitions}};
        json sm(sm_t);
        return sm;
    }

};