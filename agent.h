#ifndef __AGENT_H
#define __AGENT_H

#include <iostream>
#include <vector>

#include "state.h"
#include "maze.h"

using namespace std;

class maze;

class agent {
public:
    agent(float center, float left, float right, maze &map);
    void valueIterate(float err);
    void tdQlearning(float err);
    void startReset();
    
    vector <float> RMS;

private:
    int     selectaction(states *state);
    float   optimalU(states * state) ;
    states *takeAction(int direction);

    states * curr;
    states * next;

    float   gamma;
    float   Rp;
    int     Ne;

    maze *  world;

    float   center;
    float   left;
    float   right;
};

#endif