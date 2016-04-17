// File: Agent.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include "Agent.h"
#include "Resource.h"

namespace Gaming {

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Gaming::Game &g, const Gaming::Position &p, double energy) : Piece (g, p), __energy(energy)
    { }

    Agent::~Agent() {

    }

    void Agent::age() {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other) {
        return other.interact(this);
    }

    Piece &Agent::interact(Agent *agent) {
        if (__energy == agent->getEnergy()) {
            finish();
            agent->finish();
        } else if (__energy > agent->getEnergy()) {
            __energy -= agent->getEnergy();
            agent->finish();
        } else if (__energy < agent->getEnergy()) {
            finish();
        }

        return *this;
    }

    Piece &Agent::interact(Resource *r) {
        addEnergy(r->consume());
        return *this;
    }

}









