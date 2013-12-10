#ifndef __MAZE_H
#define __MAZE_H

#include <iostream>
#include "state.h"
#include "agent.h"

class agent;

class maze {
public:
	maze();
	bool isWall(int i, int j);
	bool isTerminal(int i, int j);
    

    states * state[6][6];
    states * start;
    states * terminal;
    


private:
	void setTerminal(int i, int j, int val);
	char feature[6][6];
};

#endif
