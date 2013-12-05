#include <iostream>
#include <cmath>
#include "maze.h"

using namespace std;

map::map() {

    for (int i=0; i<6;i++) {
        for (int j=0; j<6; j++) {
            feature[i][j]='*';
            state[i][j] = new node(i,j);    //create node
        }
    }
    
    terminal=new node(-1,-1);        //terminal state
    terminal->expUtil=0;
    terminal->R=0;
    
    feature[0][3]='W';
    feature[1][1]='W';
    feature[1][3]='W';
    feature[2][1]='W';
    feature[3][1]='W';
    feature[0][5]='T';
    feature[4][3]='T';
    feature[4][5]='T';
    feature[5][2]='T';
    feature[5][3]='T';
    feature[5][5]='T';
    
    start = state[5][0];
    
    
    for (int i=0; i<6;i++) {
        for (int j=0; j<6; j++) {
            
            //initially assign the directren pointers to point self
            state[i][j]->direct[1] = state[i][j];
            state[i][j]->direct[2] = state[i][j];
            state[i][j]->direct[3] = state[i][j];
            state[i][j]->direct[4] = state[i][j];
            
            
            if (i>0) {
                if (feature[i-1][j]=='W') 
                    state[i][j]->direct[1]=state[i][j];
                else
                    state[i][j]->direct[1]=state[i-1][j];
            }

            if(i<5) {
                if (feature[i+1][j]=='W')
                    state[i][j]->direct[3]=state[i][j];
                else
                    state[i][j]->direct[3]=state[i+1][j];
            }
            
            if (j<5) {
                
                if (feature[i][j+1]=='W')
                    state[i][j]->direct[2]=state[i][j];
                else
                    state[i][j]->direct[2]=state[i][j+1];

            }
            
            if(j>0) {
                if (feature[i][j-1]=='W')
                    state[i][j]->direct[4]=state[i][j];
                else
                    state[i][j]->direct[4]=state[i][j-1];
            }

            
            state[i][j]->direct[0] = state[i][j]->direct[4];
            state[i][j]->direct[5] = state[i][j]->direct[1];
            
            state[i][j]->R=-0.04;
        }
    }
    
    setTerminal(0,5,1);
    setTerminal(4,3,-1);
    setTerminal(4,5,-1);
    setTerminal(5,2,-1);
    setTerminal(5,3,-1);
    setTerminal(5,5,1);
    
    for (int i=0; i<6; i++) {
        for (int j=0;j<6;j++) {
            cout<<feature[i][j]<<" ";
        }
        cout<<endl;
    }
}
void map::setTerminal(int i, int j, int val){
    state[i][j]->R=1;
    state[i][j]->expUtil=1;
    for (int k=0; k<4; k++) {
        state[i][j]->Q[k]=1;
    }
    for (int k=0; k<6; k++) {
      state[i][j]->direct[k]=terminal;
    }
}
float map::optimalU(node * state,agent & robot) {
    int policy = 1;
    
    float maxU   =  (robot.center * state->direct[1]->expUtil) + 
                    (robot.left * state->direct[0]->expUtil) + 
                    (robot.right * state->direct[2]->expUtil);

    for (int i = 2; i < 5; i++) {
        float tempU =   (robot.center * state->direct[i]->expUtil) + 
                        (robot.left * state->direct[i-1]->expUtil) + 
                        (robot.right * state->direct[i+1]->expUtil);
        
        if (tempU > maxU) {
            maxU = tempU;
            policy = i;
        }
    }
    
    state->optimalpolicy_U = policy;
    return maxU;
}

void map::valueIter(float err, agent & robot) {
    float DiffU;
    int stop=0;
    
    for(iternum=0; iternum < 50; iternum++) {
        stop=1;
        for (int i=0; i<6;i++) {
            for (int j=0; j<6; j++) {
                state[i][j]->HistoryU.push_back(state[i][j]->expUtil);
                state[i][j]->expUtilNext=state[i][j]->R+robot.gamma*optimalU(state[i][j], robot);

        
                DiffU=abs(state[i][j]->expUtilNext-state[i][j]->expUtil);
                if (DiffU > err) {        // if this update is not stable, then stop=0 means we need another iteration
                    stop=0;
                } 
                state[i][j]->expUtil=state[i][j]->expUtilNext;
                
                
            }
        }    
    }
}