// File: Simple.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include "Simple.h"

namespace Gaming {

    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Gaming::Game &g, const Gaming::Position &p, double energy) : Agent(g, p, energy) {

    }

    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {
        os << SIMPLE_ID << *this;
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        ActionType arr[9] = { N, NE, NW, E, W, SE, SW, S, STAY };

        for (int i = 0; i < 9; i++) {
            if ((s.array[i] == ADVANTAGE) || (s.array[i] == FOOD))
                return arr[i];
        }
        for (int i = 0; i < 9; i++) {
            if (s.array[i] == EMPTY)
                return arr[i];
        }
        return STAY;
    }

}





