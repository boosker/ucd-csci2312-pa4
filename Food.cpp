// File: Food.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include "Food.h"

namespace Gaming {

    const char Food::FOOD_ID = 'F';


    Food::Food(const Gaming::Game &g, const Gaming::Position &p, double capacity) : Resource(g, p, capacity)
    { }

    Food::~Food() {

    }

    void Food::print(std::ostream &os) const {
        os << FOOD_ID << *this;
    }

}



