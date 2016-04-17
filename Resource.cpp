// File: Resource.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include "Resource.h"
#include "Agent.h"

namespace Gaming {

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Gaming::Game &g, const Gaming::Position &p, double capacity) : Piece(g, p),
                                                                                            __capacity(capacity)
    { }

    Resource::~Resource() {

    }

    double Resource::consume() {
        double i = __capacity;
        __capacity = 0;
        return i;
    }

    void Resource::age() {
        __capacity -= RESOURCE_SPOIL_FACTOR;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
        return STAY;
    }

    Piece &Resource::operator*(Piece &other) {
        return other.interact(this);
    }

    Piece &Resource::interact(Agent *a) {
        a->addEnergy(consume());
        return *this;
    }

    Piece &Resource::interact(Resource *r) {
        return *this;
    }

}













