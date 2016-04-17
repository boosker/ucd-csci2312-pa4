// File: Advantage.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include "Advantage.h"

namespace Gaming {

    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Gaming::Game &g, const Gaming::Position &p, double capacity) : Resource(g, p, capacity)
    { }

    Advantage::~Advantage() {

    }

    void Advantage::print(std::ostream &os) const {
        os << ADVANTAGE_ID << *this;
    }

    double Advantage::getCapacity() const {
        return Resource::getCapacity();
    }

    double Advantage::consume() {
        return Resource::consume();
    }

}








