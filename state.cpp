#include "state.h"

states::states(int i, int j) {
    this->expUtil = 0;
    this->expUtilNext = 0;
    this->visit = 0;
    reward=0;
    
    this->i = i;
    this->j = j;
    
    finalQ=0;
    for (int k=0; k<4;k++) {
        nAct[k]=0;

        Q[k]=0;
    }

}
