#include <iostream>
#include <cmath> 
#include <ostream> 
#include <vector> 
#include "header.h"
using namespace std; 

game::game(){
    player1_ = new player(1); 
    player2_ = new player(2); 
    currplayer_ = player1_; 
    myboard_ = new board(player1_, player2_); 
};

bool game::validmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    //determine the piece at the source location
    piece* selectedpiece = myboard.getpiece(srcR, srcC);

    //determine if the move is within bounds of the board
    if(destR < 0 || destR > 7 || srcR < 0 || srcR > 7){
        return false; 
    }

    //determine if the move is within the allowed movements of the piece and nothing blocking if applicable
    if(!selectedpiece->checkmove(srcR, srcC, destR, destC, myboard, currplayer)){
        return false; 
    }

    //all conditions met
    return true;
};

void game::movepiece(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    //if the piece at the destination location is not a blank and is opponent's piece
    if(myboard.getpiece(destR, destC)->type_ != "**"){
        if(myboard.getpiece(destR, destC)->myplayer_->playernum_ != currplayer.playernum_){
            //add the piece to the opponent's list of fallen pieces
            myboard.getpiece(destR, destC)->myplayer_->fallen.push_back(myboard.getpiece(destR, destC));
            //update the score for the current player
            currplayer.score_ += myboard.getpiece(destR, destC)->value_; 
            //replace the piece at the destination location with a blank
            myboard.visualboard_[destR][destC] = new blankpiece(); 
        }
    }
    //update the number of moves for the current player 
    currplayer.nummoves_++; 
    //swap the source and destination locations of the array 
    piece* tmp = myboard.getpiece(destR, destC);
    myboard.visualboard_[destR][destC] = myboard.getpiece(srcR, srcC);
    myboard.visualboard_[srcR][srcC] = tmp; 
};

bool game::checkwin(){
    //player 1
    int p1size = player1_ -> fallen.size();
    for(int i=0; i < p1size; i++){
        if(player1_ -> fallen[i]->type_ == "wE"){
            return true; 
        }
    }

    //player2
    int p2size = player2_ -> fallen.size(); 
    for(int i=0; i < p2size; i++){
        if(player2_ -> fallen[i]->type_ == "bE"){
            return true; 
        }
    }

    //neither player won
    return false; 
}

void game::nextplayer(){
    if(currplayer_ == player1_){
        currplayer_ = player2_; 
    }
    else{
        currplayer_ = player1_; 
    }
}
