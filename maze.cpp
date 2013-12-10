#include <iostream>
#include <cmath>
#include "maze.h"

using namespace std;

maze::maze() {

    for (int i=0; i<6;i++) {
        for (int j=0; j<6; j++) {
            feature[i][j]='*';
            state[i][j] = new states(i,j);    //create states
        }
    }
    
    terminal = new states(-1,-1);        //terminal state
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

            if (i<5) {
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
            
            if (j>0) {
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
}
void maze::setTerminal(int i, int j, int val){
    state[i][j]->R=val;
    state[i][j]->expUtil=val;
    for (int k=0; k<4; k++) {
        state[i][j]->Q[k]=val;
    }
    for (int k=0; k<6; k++) {
      state[i][j]->direct[k]=terminal;
    }
}

bool maze::isWall(int i, int j){
    return feature[i][j] == 'W';
}
bool maze::isTerminal(int i, int j){
    return feature[i][j] == 'T';
}