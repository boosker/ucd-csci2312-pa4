// File: AggressiveAgentStrategy.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming {

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) : __agentEnergy(agentEnergy)
    { }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {

    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        ActionType arr[9] = { N, NE, NW, E, W, SE, SW, S, STAY };

        for (int i = 0; i < 9; i++) {
            if ((__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) &&
                    ((s.array[i] == SIMPLE) || (s.array[i] == STRATEGIC)))
                return arr[i];
        }
        for (int i = 0; i < 9; i++) {
            if (s.array[i] == ADVANTAGE)
                return arr[i];
        }
        for (int i = 0; i < 9; i++) {
            if (s.array[i] == FOOD)
                return arr[i];
        }
        for (int i = 0; i < 9; i++) {
            if (s.array[i] == EMPTY)
                return arr[i];
        }
        return STAY;
    }

}



