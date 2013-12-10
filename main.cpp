#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "agent.h"
#include "state.h"
#include "maze.h"

using namespace std;
string mapDirt(int d) {
    switch(d){
        case 1: return "↑";
        case 2: return "→";
        case 3: return "↓";
        case 4: return "←";
    }
}

void output(agent &robot, maze &world) {
    ofstream valiter("result/ValIter.txt");
    ofstream qlearn("result/QLearning.txt");
    ofstream figureV("result/FigureV.csv");
    ofstream figureQ("result/FigureQ.csv");
    ofstream rmserror("result/RMSerror.csv");
       
    valiter<<"Value Iteration utilities"<<endl;
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.isWall(i,j)) {
                valiter<<setw(10)<<'#';
            }
            else
                valiter<<setprecision(6)<<setw(10)<<world.state[i][j]->expUtil;
        }
        valiter<<endl;
    }
    valiter<<endl;
    
    valiter<<"Value Iteration optimal policy"<<endl;

    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.isWall(i,j)) {
                valiter<<'#'<<"\t";
            }
            else if (world.isTerminal(i,j)) {
                valiter<<'T'<<"\t";
            }
            else
                valiter<<setprecision(6)<<mapDirt(world.state[i][j]->optimalpolicy_U)<<"\t";
        }
        valiter<<endl;
    }

    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.isWall(i,j)) {
                    
            }
            else
                figureV<<setprecision(6)<<i<<","<<j<<";";
        }
    }
    
    
    figureV<<endl;

    for (int k = 0; k < 50; k++) {

        for (int i=0; i<6; i++) {
            for (int j=0; j<6; j++) {
                if (world.isWall(i,j)) {
                    
                }
                else
                    figureV<<setprecision(6)<<world.state[i][j]->hist_V[k]<<";";
                
            }
        }
        figureV<<endl;
    }
        

    
    
    qlearn<<"TDQ utility estimates"<<endl;
    
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.isWall(i,j)) {
                qlearn<<setw(10)<<'#';
            }
            else
                qlearn<<setprecision(6)<<setw(10)<<world.state[i][j]->Qfinal;
        }
        qlearn<<endl;
    }
    
    qlearn<<endl;

    qlearn<<"TDQ learned policy"<<endl;
    
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.isWall(i,j)) {
                qlearn<<'#'<<"\t";
            }
            else if (world.isTerminal(i,j)) {
                qlearn<<'T'<<"\t";
            }
            else
                qlearn<<setprecision(6)<<mapDirt(world.state[i][j]->optimalpolicy_Q)<<"\t";
        }
        qlearn<<endl;
    }



    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.isWall(i,j)) {
                    
            }
            else
                figureQ<<setprecision(6)<<i<<","<<j<<";";
            
        }
    }
    
    
    figureQ<<endl;

    for (int k=0; k < 50; k++) {

        for (int i=0; i<6; i++) {
            for (int j=0; j<6; j++) {
                if (world.isWall(i,j)) {
                    
                }
                else
                    figureQ<<setprecision(6)<<world.state[i][j]->hist_Q[k]<<";";
                
            }
        }
        figureQ<<endl;
    }


    for (int k=0; k<robot.RMS.size(); k++) {
        rmserror<<k+1<<","<<robot.RMS[k]<<endl;
    }
    
    valiter.close();
    qlearn.close();
    figureV.close();
    figureQ.close();
    rmserror.close();
}

int main() {

    srand((unsigned)time(NULL));
    
    maze  world;
    agent robot(0.8, 0.1, 0.1, world);
    robot.valueIter(0.0001);
    
    robot.curr = world.start;
    robot.TDQ(0.0001);
    
    cout << "FINISH\n";
    
    output(robot, world);
    
    return 0;
}