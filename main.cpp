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

void output(agent &robot, map &world) {
    ofstream valiter("result/ValIter.txt");
    ofstream qlearn("result/QLearning.txt");
    ofstream figure("result/Figure.csv");
    
    valiter<<"Value Iteration utilities"<<endl;
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.feature[i][j]=='W') {
                valiter<<setw(10)<<'#';
            }
            else
                valiter<<setprecision(4)<<setw(10)<<world.state[i][j]->expUtil;
        }
        
        
        valiter<<endl;
    }
    valiter<<endl;
    
    valiter<<"Value Iteration optimal policy"<<endl;

    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.feature[i][j]=='W') {
                valiter<<'#'<<"\t";
            }
            else
                valiter<<setprecision(4)<<mapDirt(world.state[i][j]->optimalpolicy_U)<<"\t";
        }
        valiter<<endl;
    }

    
    
    qlearn<<"TDQ utility estimates"<<endl;
    
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.feature[i][j]=='W') {
                qlearn<<setw(10)<<'#';
            }
            else
                qlearn<<setprecision(4)<<setw(10)<<world.state[i][j]->Qfinal;
        }
        qlearn<<endl;
    }
    
    qlearn<<endl;

    qlearn<<"TDQ learned policy"<<endl;
    
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.feature[i][j]=='W') {
                qlearn<<'#'<<"\t";
            }
            else
                qlearn<<setprecision(4)<<mapDirt(world.state[i][j]->optimalpolicy_Q)<<"\t";
        }
        qlearn<<endl;
    }

    
    for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
            if (world.feature[i][j]=='W') {
                
            }
            else
                figure<<setprecision(4)<<world.state[i][j]->i<<","<<world.state[i][j]->j<<";";
        }
    }
    
    
    figure<<endl;

    for (int k=0; k<world.iternum; k++) {

        for (int i=0; i<6; i++) {
            for (int j=0; j<6; j++) {
                if (world.feature[i][j]=='W') {

                }
                else
                    figure<<setprecision(4)<<world.state[i][j]->HistoryU[k]<<";";
            }
        }
        
        figure<<endl;
    }
        

    qlearn<<"RMS error function"<<endl;;

    for (int k=0; k<robot.RMS.size(); k++) {
        qlearn<<robot.RMS[k]<<endl;
    }
    
    valiter.close();
    qlearn.close();
    figure.close();
}

int main() {

    srand((unsigned)time(NULL));
    agent robot(0.8, 0.1, 0.1);
    map world;
    
    robot.curr = world.start;
    robot.mapp = &world;
    
    world.valueIter(0.0001, robot);
    
    robot.curr = world.start;
    robot.TDQ(0.0001);
    
    cout << "FINISH\n";
    
    output(robot, world);
    
    return 0;
}