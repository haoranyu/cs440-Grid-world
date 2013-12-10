#include <cstdio>
#include <ctime>
#include <iostream>
#include <cmath>
#include <cstdlib>

#include "agent.h"

using namespace std;

agent::agent(float center, float left, float right, maze &map) {

    this->center = center;
    this->left = left;
    this->right = right;

    this->curr = map.start;
    this->world = &map;

    this->gamma = 0.99;
    this->Rp = 2;
    this->Ne = 10;
}

void agent::startReset(){
    curr = world->start;
}

states * agent::takeAction(int direction) {
    int randnum = rand()%10;
    
    if (randnum == 0)
        return curr->direct[direction+1];
    else if (randnum == 1)
        return curr->direct[direction-1];
    else
        return curr->direct[direction];
}

void agent::valueIterate(float err) {
    for (int h=0; h < 50; h++) {
        for (int i=0; i<6;i++) {
            for (int j=0; j<6; j++) {
                world->s[i][j]->hist_V.push_back(world->s[i][j]->expUtil);
                world->s[i][j]->expUtilNext = world->s[i][j]->reward+this->gamma*this->optimalU(world->s[i][j]);
                world->s[i][j]->expUtil = world->s[i][j]->expUtilNext;
            }
        }    
    }
}

float agent::optimalU(states * state) {
    int policy = 1;
    
    float maxU   =  (this->center * state->direct[1]->expUtil) + 
                    (this->left * state->direct[0]->expUtil) + 
                    (this->right * state->direct[2]->expUtil);

    for (int i = 2; i < 5; i++) {
        float tempU =   (this->center * state->direct[i]->expUtil) + 
                        (this->left * state->direct[i-1]->expUtil) + 
                        (this->right * state->direct[i+1]->expUtil);
        
        if (tempU > maxU) {
            maxU = tempU;
            policy = i;
        }
    }
    
    state->optimalpolicy_U = policy;
    return maxU;
}


void agent::tdQlearning(float err) {
    int     act,
            act_next;

    float   alpha = 1,
            temp = 0,
            maxQ = -9999;

    for (int h = 0; h < 2000; h++) {
        
        curr = world->start;
        
        act=selectaction(curr);
        while (curr->i!=-1) {

            next=takeAction(act);   
            curr->visit++;
            curr->NAction[act-1]+=1;

            alpha=60.0/(59+curr->NAction[act-1]);

            act_next=selectaction(next); 

            temp=0;
            maxQ=-999;
            
            for (int k=0; k<4; k++) {
                temp=next->Q[k];
                if (temp>maxQ) {
                    maxQ=temp;
                }
            }

            curr->Q[act-1]=curr->Q[act-1]+alpha*(curr->reward+gamma*maxQ-curr->Q[act-1]);
            
            curr=next;
            act=act_next;
        }

    
        float       RMSE_temp = 0;
        int         action = 0;
        states *    temp_s = NULL;

        for (int i=0; i<6; i++) {
            for (int j=0; j<6; j++) {
                temp=0;
                maxQ=-9999;
                
                temp_s=world->s[i][j];
                for (int k=0; k<4; k++) {
                    temp=temp_s->Q[k];
                    
                    if (temp > maxQ) {
                        maxQ = temp;
                        action = k+1;
                    }
                }
                
                temp_s->Qfinal=maxQ;
                temp_s->hist_Q.push_back(temp_s->Qfinal);
                temp_s->optimalpolicy_Q=action;
                
                if (!(world->isWall(i,j)) && !(world->isTerminal(i, j))) {
                    RMSE_temp+=(temp_s->expUtil-maxQ)*(temp_s->expUtil-maxQ)/25;
                }
            }
        }
        RMS.push_back(sqrt(RMSE_temp));
    }
}

int agent::selectaction(states * state) {
    float maxQ=-999;
    float temp=0;
    int action=-1;
    int N;
    float ratio;

    for (int i=1; i<5; i++) {
        ratio=rand()/(double(RAND_MAX));
        N=state->NAction[i-1];
        
        if (N<Ne)
            temp = Rp *(1+ratio); 
        else
            temp = state->Q[i-1];
                
        if (temp>maxQ) {
            maxQ=temp;
            action = i;
        }
    }

    return action;
}