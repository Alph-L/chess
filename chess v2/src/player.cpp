#include <iostream> 
#include "header.h"
using namespace std; 

player::player(){
    score_ = 0; 
    nummoves_ = 0; 
    id_ = '0';
}; 

player::player(char id){
    score_ = 0; 
    nummoves_ = 0; 
    id_ = id; 
}; 

player::~player(){};

char player::getid(){
    return id_; 
}

void player::addscore(int add){
    score_ += add; 
}
