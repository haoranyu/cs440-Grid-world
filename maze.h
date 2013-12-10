#ifndef __MAZE_H
#define __MAZE_H

#include <iostream>
#include "state.h"
#include "agent.h"

class agent;

class maze {
public:
	maze();

    void setTerminal(int i, int j, int val);


    char feature[6][6];
    
    states * state[6][6];
    states * start;
    states * terminal;
    
    int iternum;
};

#endif
