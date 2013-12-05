#ifndef __MAZE_H
#define __MAZE_H

#include <iostream>
#include "state.h"
#include "agent.h"

class agent;

class maze {
public:
	maze();
	void valueIter(float err, agent & player);
    void setTerminal(int i, int j, int val);
    
    float optimalU(node * state, agent & player);

    char feature[6][6];
    
    node * state[6][6];
    node * start;
    node * terminal;
    
    int iternum;
};

#endif
