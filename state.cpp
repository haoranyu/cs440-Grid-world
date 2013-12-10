#include "state.h"

states::states(int i, int j) {
    this->expUtil = 0;
    this->expUtilNext = 0;
    this->visit = 0;
    R=0;
    
    this->i = i;
    this->j = j;
    
    Qfinal=0;
    for (int k=0; k<4;k++) {
        NAction[k]=0;

        Q[k]=0;
    }

}
