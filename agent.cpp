#include "agent.h"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

agent::agent(float center, float left, float right) {
    this->center = center;
    this->left = left;
    this->right = right;

    this->gamma = 0.99;
    Rp = 2;
    Ne = 10;
}


states * agent::going(int direction) {
    int randnum = rand()%10;
    states * nextstate;
    
    if(randnum == 0)
        return curr->direct[direction+1];
    else if(randnum == 1)
        return curr->direct[direction-1];
    else
        return curr->direct[direction];
}

void agent::valueIter(float err) {
    float DiffU;
    int stop=0;
    
    for (iternum=0; iternum < 50; iternum++) {
        stop=1;
        for (int i=0; i<6;i++) {
            for (int j=0; j<6; j++) {
                mapp->state[i][j]->HistoryU.push_back(mapp->state[i][j]->expUtil);
                mapp->state[i][j]->expUtilNext=mapp->state[i][j]->R+this->gamma*this->optimalU(mapp->state[i][j]);

        
                DiffU=abs(mapp->state[i][j]->expUtilNext-mapp->state[i][j]->expUtil);
                if (DiffU > err) {        // if this update is not stable, then stop=0 means we need another iteration
                    stop=0;
                } 
                mapp->state[i][j]->expUtil=mapp->state[i][j]->expUtilNext;
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


void agent::TDQ(float err) {
    int a,a_next;
    float alpha=1;
    float temp=0;
    float maxQ=-9999;
    float Diff;
    int action;
    
    states * temppointer=NULL;

    
    Diff=999;
    float RMSE_temp=0;
    
    for(iternum=0; iternum < 7000; iternum++) {
        
        curr = mapp->start;        //initialize the starting state
        
        a=selectaction(curr);           //choose a from the initial state

        while(curr->i!=-1) {

            next=going(a);   
            curr->visit++;
            curr->NAction[a-1]+=1;

            alpha=60.0/(59+curr->NAction[a-1]);

            a_next=selectaction(next); 

            temp=0;
            maxQ=-999;
            
            for (int k=0; k<4; k++) {
                temp=next->Q[k];
                if (temp>maxQ) {
                    maxQ=temp;
                }
            }

            curr->Q[a-1]=curr->Q[a-1]+alpha*(curr->R+gamma*maxQ-curr->Q[a-1]);
            
            curr=next;
            a=a_next;
            
        }

    
        RMSE_temp=0;
        action=0;
        
        for (int i=0; i<6; i++) {
            for (int j=0; j<6; j++) {
                temp=0;
                maxQ=-9999;
                
                temppointer=mapp->state[i][j];
                for (int k=0; k<4; k++) {
                    temp=temppointer->Q[k];
                    
                    if (temp > maxQ) {
                        maxQ = temp;
                        action = k+1;
                    }
                }
                
                temppointer->Qfinal=maxQ;
                temppointer->QHistoryU.push_back(temppointer->Qfinal);
                temppointer->optimalpolicy_Q=action;
                
                if (mapp->feature[i][j]!='W'&& mapp->feature[i][j]!='T') {
                    RMSE_temp+=(temppointer->expUtil-maxQ)*(temppointer->expUtil-maxQ)/25;
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