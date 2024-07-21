#include <iostream> 
#include "header.h"
using namespace std; 

game::game(){
    myboard_ = new board(); 
    white_ = new player('w'); 
    black_ = new player('b'); 
    currplayer_ = white_; 
};

game::~game(){
    delete myboard_; 
    delete white_; 
    delete black_; 
};

bool game::validmove(int srcR, int srcC, int destR, int destC){
    //check input is within bounds of the board
    if(srcR > 7 || srcR < 0 || srcC > 7 || srcC < 0 || destR > 7 || destR < 0 || destC > 7 || destC < 0){
        return false; 
    }

    //cout << "TEST WITHIN BOUNDS" << endl; 

    //check the piece is your own
    if(myboard_ -> getpiece(srcR, srcC) -> getowner() != currplayer_ -> getid()){
        cout << "PIECE OWNER = " << myboard_ -> getpiece(srcR, srcC) -> getowner() << endl; 
        cout << "CURRENT PLAYER = " << currplayer_ -> getid() << endl; 
        return false; 
    }

    //cout << "TEST PIECE IS YOUR OWN" << endl; 

    //check the move follows the piece pattern and nothing blocking
    if(!(myboard_ -> getpiece(srcR, srcC) -> checkmove(srcR, srcC, destR, destC, *myboard_, *currplayer_))){
        return false; 
    }

    //cout << "TEST PATTEN MATCHED AND NOTHING BLOCKED" << endl; 

    return true; 
};

void game::swap(int srcR, int srcC, int destR, int destC){
    //if taking opponent, add piece to opponent's fallen list, add score to current player, replace with blank piece
    if(myboard_-> getpiece(destR, destC) -> getowner() != 'n' || myboard_-> getpiece(destR, destC) -> getowner() != currplayer_ -> getid()){
        currplayer_ -> taken.push_back(myboard_-> getpiece(destR, destC)); //add piece to current player's list of taken 
        currplayer_ -> addscore(myboard_-> getpiece(destR, destC) -> getvalue()); //add score to current player
        myboard_ -> replace(destR, destC, "blank", *currplayer_); //replace the opponent's piece with a blank piece
    }
    //swap 
    myboard_ -> swap(srcR, srcC, destR, destC);
};

void game::nextplayer(){
    if(currplayer_ -> getid() == 'w'){
        currplayer_ = black_; 
    }
    else{
        currplayer_ = white_; 
    }
};

board* game::getboard(){
    return myboard_; 
};

player* game::getcurrplayer(){
    return currplayer_; 
};

bool game::checkwin(){
    for(int i=0; i<white_ -> taken.size(); i++){
        if(white_ -> taken[i] -> gettype() == "bK"){
            return true; 
        }
    }
    for(int i=0; i<black_ -> taken.size(); i++){
        if(black_ -> taken[i] -> gettype() == "wK"){
            return true; 
        }
    }

    return false; 
}

