#include <iostream>
#include <cmath>
#include "maze.h"

using namespace std;

maze::maze() {

    for (int i = 0; i < 6;i++) {
        for (int j = 0; j < 6; j++) {
            feature[i][j]='*';
            s[i][j] = new states(i,j);
        }
    }
    
    setWall(0, 3);
    setWall(1, 1);
    setWall(1, 3);
    setWall(2, 1);
    setWall(3, 1);
    
    start = s[5][0];
    
    
    for (int i=0; i < 6;i++) {
        for (int j=0; j < 6; j++) {
            
            s[i][j]->direct[1] = s[i][j];
            s[i][j]->direct[2] = s[i][j];
            s[i][j]->direct[3] = s[i][j];
            s[i][j]->direct[4] = s[i][j];
            
            
            if (i>0) {
                if (feature[i-1][j] == 'W') 
                    s[i][j]->direct[1] = s[i][j];
                else
                    s[i][j]->direct[1] = s[i-1][j];
            }

            if (i < 5) {
                if (feature[i+1][j] == 'W')
                    s[i][j]->direct[3] = s[i][j];
                else
                    s[i][j]->direct[3] = s[i+1][j];
            }
            
            if (j < 5) {
                
                if (feature[i][j+1] == 'W')
                    s[i][j]->direct[2] = s[i][j];
                else
                    s[i][j]->direct[2] = s[i][j+1];
            }
            
            if (j>0) {
                if (feature[i][j-1] == 'W')
                    s[i][j]->direct[4] = s[i][j];
                else
                    s[i][j]->direct[4] = s[i][j-1];
            }

            
            s[i][j]->direct[0] = s[i][j]->direct[4];
            s[i][j]->direct[5] = s[i][j]->direct[1];
            
            s[i][j]->reward=-0.04;
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
    feature[i][j] = 'T';

    states * temp = new states(-1,-1);
    temp->expUtil = 0;
    temp->reward = 0;


    s[i][j]->reward=val;
    s[i][j]->expUtil=val;
    for (int k=0; k < 4; k++) {
        s[i][j]->Q[k]=val;
    }
    for (int k=0; k < 6; k++) {
      s[i][j]->direct[k] = temp;
    }
}
void maze::setWall(int i, int j){
    feature[i][j] = 'W';
}
bool maze::isWall(int i, int j){
    return feature[i][j] == 'W';
}
bool maze::isTerminal(int i, int j){
    return feature[i][j] == 'T';
}