#ifndef __STATE_H
#define __STATE_H

#include <iostream>
#include <vector>

using namespace std;

class states {
public:

    states(int i, int j);

    states * direct[6];

    float expUtil;
    float reward;
    
    float expUtilNext;
    
    int i, j;
    
    float Q[4];
    
    float finalQ;
    
    int nAct[4];
    int visit;
    
    int policy_Q;
    int policy_U;
    
    vector<float> hist_V;
    vector<float> hist_Q;
};

#endif