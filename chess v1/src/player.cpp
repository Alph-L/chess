#include <iostream>
#include <cmath> 
#include <ostream> 
#include <vector> 
#include "header.h"
using namespace std; 



player::player(){
};



player::player(int playernum){
    score_ = 0; 
    nummoves_ = 0; 
    playernum_ = playernum; 
};