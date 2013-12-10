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
    
    states * s[6][6];
    states * start;

private:
	void setTerminal(int i, int j, int val);
	void setWall(int i, int j);
	char feature[6][6];
};

#endif
