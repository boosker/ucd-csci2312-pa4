// File: Game.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include <vector>
#include <array>
#include "Agent.h"
#include "Game.h"
#include "Strategic.h"
#include "Simple.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming {

    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    PositionRandomizer Game::__posRandomizer;

    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

        while (numStrategic > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }

        while (numSimple > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple --;
            }
        }

        while (numAdvantages > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages --;
            }
        }

        while (numFoods > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods --;
            }
        }
    }

    Game::Game() : __width(MIN_WIDTH), __height(MIN_HEIGHT), __round(0),
                   __status(NOT_STARTED), __verbose(false),
                   __numInitAgents(NUM_INIT_AGENT_FACTOR), __numInitResources(NUM_INIT_RESOURCE_FACTOR),
                   __grid((__width * __height), nullptr)
    {
        //populate();
    }

    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height), __round(0),
                                                               __status(NOT_STARTED), __verbose(false),
                                                               __grid((__width * __height), nullptr)
    {
        if (width < MIN_WIDTH || height < MIN_HEIGHT)
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);

        if (!manual)
            populate();
    }

//    Game::Game(const Game &another) : __width(another.__width), __height(another.__height), __round(another.__round),
//                                      __status(another.__status), __verbose(another.__verbose),
//                                      __numInitAgents(another.__numInitAgents),
//                                      __numInitResources(another.__numInitResources), __grid(another.__grid)
//    { }

    Game::~Game() {
        for (int i = 0; i < __grid.size(); ++i) {
            delete __grid[i];
        }
    }

    unsigned int Game::getNumPieces() const {
        unsigned int numPieces = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Piece *piece = dynamic_cast<Piece*>(*it);
            if (piece) numPieces ++;
        }
        return numPieces;
    }
    unsigned int Game::getNumAgents() const {
        unsigned int numAgents = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Agent *agent = dynamic_cast<Agent*>(*it);
            if (agent) numAgents ++;
        }
        return numAgents;
    }
    unsigned int Game::getNumSimple() const {
        unsigned int numAgents = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Agent *agent = dynamic_cast<Simple*>(*it);
            if (agent) numAgents ++;
        }
        return numAgents;
    }
    unsigned int Game::getNumStrategic() const {
        unsigned int numAgents = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Agent *agent = dynamic_cast<Strategic*>(*it);
            if (agent) numAgents ++;
        }
        return numAgents;
    }
    unsigned int Game::getNumResources() const {
        unsigned int numResources = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Resource *resource = dynamic_cast<Resource*>(*it);
            if (resource) numResources ++;
        }
        return numResources;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const {
        unsigned int i = (__width * x) + y;
        if (__grid[i] == nullptr)
            throw PositionEmptyEx(x, y);
        Piece* piece = __grid[i];
        //PieceType hi = __grid[i]->getType();

        //bool pass = __grid[i]->getType() == PieceType::SIMPLE;

        return piece;
    }

    void Game::addSimple(const Position &position) {
        unsigned int i = (__width * position.x) + position.y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(position.x, position.y);

        __grid[i] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }
    void Game::addSimple(const Position &position, double energy) {
        unsigned int i = (__width * position.x) + position.y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(position.x, position.y);

        __grid[i] = new Simple(*this, position, energy);
    }
    void Game::addSimple(unsigned x, unsigned y) {
        unsigned int i = (__width * x) + y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(x, y);
        Position pos(x, y);

        __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
    }
    void Game::addSimple(unsigned x, unsigned y, double energy) {
        unsigned int i = (__width * x) + y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(x, y);
        Position pos(x, y);

        __grid[i] = new Simple(*this, pos, energy);
    }
    void Game::addStrategic(const Position &position, Strategy *s) {
        unsigned int i = (__width * position.x) + position.y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(position.x, position.y);

        __grid[i] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }
    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        unsigned int i = (__width * x) + y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(x, y);
        Position pos(x, y);

        __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY, s);
    }
    void Game::addFood(const Position &position) {
        unsigned int i = (__width * position.x) + position.y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(position.x, position.y);

        __grid[i] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    void Game::addFood(unsigned x, unsigned y) {
        unsigned int i = (__width * x) + y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(x, y);
        Position pos(x, y);

        __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
    }
    void Game::addAdvantage(const Position &position) {
        unsigned int i = (__width * position.x) + position.y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(position.x, position.y);

        __grid[i] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    void Game::addAdvantage(unsigned x, unsigned y) {
        unsigned int i = (__width * x) + y;
        if (i < 0 || i > __grid.size() - 1)
            throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[i] != nullptr)
            throw PositionNonemptyEx(x, y);
        Position pos(x, y);

        __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
    }
    const Surroundings Game::getSurroundings(const Position &pos) const {
        Surroundings s;
        int x = pos.x, y = pos.y, gridCount;
        gridCount = (__width * (x-1)) + (y-1);      // Starting point for s.array
        for (int i = 0; i < 9; i++) {
            s.array[i] = EMPTY;
        }

        if (gridCount < 0) {
            for (int i = 0; i < 9; i++) {

                // Make s.array inaccessible up to the beginning of the __grid vector
                s.array[i] = INACCESSIBLE;

                // Beginning of the vector __grid
                if (gridCount == 0) {
                    for (int j = i; j < 9; j++) {
                        if (__grid[gridCount] == nullptr)
                            s.array[j] = EMPTY;
                        else if (__grid[gridCount]->getType() == ADVANTAGE)
                            s.array[i] = ADVANTAGE;
                        else if (__grid[gridCount]->getType() == FOOD)
                            s.array[i] = FOOD;
                        else if (__grid[gridCount]->getType() == SIMPLE)
                            s.array[i] = SIMPLE;
                        else if (__grid[gridCount]->getType() == STRATEGIC)
                            s.array[i] = STRATEGIC;
                        else s.array[j] = EMPTY;
                        gridCount++;
                    }
                    break;
                }
                gridCount++;
            }
            s.array[4] = SELF;
        } else {
            for (int i = 0; i < 9; i++) {
                // If it goes beyond the bounds, make it INACCESSIBLE
                if (gridCount > __grid.size() - 1) {
                    for (int j = i; j < 9; j++) {
                        if (gridCount > __grid.size() - 1)
                            s.array[j] = INACCESSIBLE;
                        gridCount++;
                    }
                    break;
                }
                if (__grid[gridCount] == nullptr)
                    s.array[i] = EMPTY;
                else if (__grid[gridCount]->getType() == ADVANTAGE)
                    s.array[i] = ADVANTAGE;
                else if (__grid[gridCount]->getType() == FOOD)
                    s.array[i] = FOOD;
                else if (__grid[gridCount]->getType() == SIMPLE)
                    s.array[i] = SIMPLE;
                else if (__grid[gridCount]->getType() == STRATEGIC)
                    s.array[i] = STRATEGIC;
                else s.array[i] = EMPTY;

                gridCount++;
            }
            s.array[4] = SELF;
        }

        return s;
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {

    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        ActionType arr[9] = { N, NE, NW, E, W, SE, SW, S, STAY };
        Surroundings surr = getSurroundings(pos);
        int index = 0;
        for (int i = 0; i < 9; i++) {
            if (arr[i] == ac) {
                index = i;
                break;
            }
        }
        return ((surr.array[index] != INACCESSIBLE) || (surr.array[index] != SELF));
    }
    const Position Game::move(const Position &pos, const ActionType &ac) const {
        ActionType arr[9] = { N, NE, NW, E, W, SE, SW, S, STAY };
        Position position;
        
        if(isLegal(ac, pos)) {
            int x = pos.x, y = pos.y, move = (__width * (x - 1)) + (y - 1);
            int index = 0;

            for (int i = 0; i < 9; i++) {
                if (arr[i] == ac) {
                    index = i;
                    break;
                }
            }
            move += index;
            position.x = __width / move, position.y = __width % move;
            return position;
        }
        else
            throw PositionEx(pos.x, pos.y);
    }
    void Game::round() {
        ActionType arr[9] = { N, NE, NW, E, W, SE, SW, S, STAY };
        Surroundings surr;
        Position to;
        int index = 0;

        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] == nullptr)
                continue;
            else if(!__grid[i]->getTurned()) {
                surr = getSurroundings(__grid[i]->getPosition());
                ActionType ac = __grid[i]->takeTurn(surr);
                to = move(__grid[i]->getPosition(), ac);
                index = (__width * to.x) + to.y;

                if (__grid[index] == nullptr) {
                    __grid[index] = __grid[i];
                    delete __grid[i];
                }
                else if (__grid[index]->getType() == SIMPLE) {
                    __grid[i]->interact((Agent *) __grid[index]);
                    if (!__grid[i]->isViable())
                        delete __grid[i];
                    else if (!__grid[index]->isViable())
                        delete __grid[index];
                } else if (__grid[index]->getType() == STRATEGIC) {
                    __grid[i]->interact((Agent *) __grid[index]);
                    if (!__grid[i]->isViable())
                        delete __grid[i];
                    else if (!__grid[index]->isViable())
                        delete __grid[index];
                } else if (__grid[index]->getType() == ADVANTAGE) {
                    __grid[i]->interact((Resource *) __grid[index]);
                    if (!__grid[index]->isViable())
                        delete __grid[index];
                } else if (__grid[index]->getType() == FOOD) {
                    __grid[i]->interact((Resource *) __grid[index]);
                    if (!__grid[index]->isViable())
                        delete __grid[index];
                }
                __grid[i]->setTurned(true);
            }
        }
        for (int i = 0; i < __grid.size(); i++) {
            if (__grid[i] != nullptr) {
                __grid[i]->age();
                __grid[i]->setTurned(false);
                if (__grid[i]->isViable())
                    delete __grid[i];
            }
        }
        ++__round;
    }
    void Game::play(bool verbose) {
        if (verbose)
            std::cout << *this;
    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        os << std::endl << "Round " << game.__round << ":" << std::endl;

        for (int i = 0; i < game.__height; i++) {
            for (int j = 0; j < game.__width; j++) {
                //if (game.__grid[i] == nullptr)
                    //os << "[     ]";
                //else
                    os << "[" << game.__grid[j] << "]";
            }
            os << std::endl;
        }

        if (game.__status == game.NOT_STARTED)
            os << "Status: Not Started" << std::endl;
        else if (game.__status == game.PLAYING)
            os << "Status: Playing..." << std::endl;
        else if (game.__status == game.OVER)
            os << "Status: Over!" << std::endl;

        return os;
    }
}