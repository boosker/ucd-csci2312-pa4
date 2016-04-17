// File: Exceptions.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include "Exceptions.h"

namespace Gaming {


    void GamingException::setName(std::string name) { __name = name; }

    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        os << ex.__name;
        return os;
    }


    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
        __exp_width = expWidth, __exp_height = expHeight, __width = width, __height = height;
    }

    unsigned DimensionEx::getExpWidth() const {
        return __exp_width;
    }

    unsigned DimensionEx::getExpHeight() const {
        return __exp_height;
    }

    unsigned DimensionEx::getWidth() const {
        return __width;
    }

    unsigned DimensionEx::getHeight() const {
        return __height;
    }


    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
        os << __name; //<< " exception thrown!" << std::endl;
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width,
                                                       unsigned height) : DimensionEx(minWidth, minHeight, width, height)
    { setName(("InsufficientDimensionsEx")); }


    void OutOfBoundsEx::__print_args(std::ostream &os) const {
        os << __name; //<< " exception thrown!" << std::endl;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height)
            : DimensionEx(maxWidth, maxHeight, width, height)
    { setName(("OutOfBoundsEx")); }


    void PositionEx::__print_args(std::ostream &os) const {
        os << __name; //<< " exception thrown!" << std::endl;
    }

    PositionEx::PositionEx(unsigned x, unsigned y) {
        setName(("PositionEx"));
    }


    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(x, y)
    { setName(("PositionNonemptyEx")); }


    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(x, y)
    { setName(("PositionEmptyEx")); }

    void PosVectorEmptyEx::__print_args(std::ostream &os) const {
        os << __name; //<< " exception thrown!" << std::endl;
    }

    PosVectorEmptyEx::PosVectorEmptyEx() {
        setName(("PosVectorEmptyEx"));
    }

}

