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
    node * curr;
    node * next;
    node * going(int direction);
    
    int iternum;        //the number of iternation;
    
    float center;    //the probability of going the right direction
    float left;       //the probability of going the left direction
    float right;      //the probability of going the right direction
    
    //float utility_sum;            //the total utility so far
    
    vector <float> RMS;          //the root mean squared error
    
    float gamma;     //the discount rate;
    
    float Rp;       //the R+ in f(u,n)
    int Ne;             //Ne
    
    agent(float center,float left,float right);
    
    maze *mapp;
    
    void TDQ(float err);
    int selectaction(node *state);
    
    int tempaction;
    
};

#endif