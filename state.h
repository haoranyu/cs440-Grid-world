#ifndef __STATE_H
#define __STATE_H

#include <iostream>
#include <vector>

using namespace std;

class node {
public:
    node * direct[6];

    float expUtil;     //the expected utility of current state
    float R;
    
    float expUtilNext;    //the expect utility of next stage;
    
    int i, j;
    node(int i, int j);
    
    float Q[4];             //the Q function 0: up  1: right, 2: down; 3: left
    
    float Qfinal;
    
    int NAction[4];         //the Ne function 0
    int visit;
    int optimalpolicy_Q;      //the optimal policy based on Q value
    int optimalpolicy_U;      //the optimal policy based on U value
    
    vector<float> HistoryU;  //the U value convergence history
};

#endif