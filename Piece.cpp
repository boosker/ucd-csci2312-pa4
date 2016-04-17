// File: Piece.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include "Piece.h"

namespace Gaming {

    unsigned int Piece::__idGen = 0;

    Piece::Piece(const Gaming::Game &g, const Gaming::Position &p) : __game(g), __position(p), __id(__idGen++),
                                                                     __finished(false), __turned(false)
    { }

    Piece::~Piece() {

    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece) {
        os << piece.__id;
        return os;
    }
}




