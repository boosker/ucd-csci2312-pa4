// File: Strategic.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include "Strategic.h"
#include "AggressiveAgentStrategy.h"
#include "DefaultAgentStrategy.h"

namespace  Gaming {

    const char Strategic::STRATEGIC_ID = 'T';

    Gaming::Strategic::Strategic(const Gaming::Game &g, const Gaming::Position &p, double energy,
                                 Gaming::Strategy *s) : Agent(g, p, energy), __strategy(s)
    { }

    Strategic::~Strategic() {

    }

    void Strategic::print(std::ostream &os) const {
        os << STRATEGIC_ID << *this;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const {
        ActionType ac = __strategy->operator()(s);
    }

}





