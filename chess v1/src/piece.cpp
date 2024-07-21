#include <iostream>
#include <cmath> 
#include <ostream> 
#include <vector> 
#include "header.h"
using namespace std; 


piece::piece(){};

piece::~piece(){}; 



blankpiece::blankpiece(){
    value_ = 0; 
    type_ = "**"; 
};

blankpiece::~blankpiece(){
    // additional delete
    piece::~piece();
};

bool blankpiece::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    return true; 
};



pawn::pawn(player* currplayer){
    value_ = 1;
    if(currplayer -> playernum_ == 1){
        type_ = "wP";
    } 
    else{
        type_ = "bP";
    }
    moved_ = false; 
    myplayer_ = currplayer; 
};

pawn::~pawn(){}; 

bool pawn::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC;
    
    //check that the movement pattern is correct
    bool validmove = false; 
    //if moved vertically, check validity 
    if(vertmov == 1 && horizmov == 0){
        validmove = true; 
    }
    else if(vertmov == 2 && horizmov == 0 && moved_ == false){
        validmove = true; 
    }  
    //if moved diagonally, check validity
    else if(vertmov == 1 && horizmov == -1 && (myboard.getpiece(destR, destC)->myplayer_->playernum_ != currplayer.playernum_)){
        validmove = true; 
    }  
    else if(vertmov == 1 && horizmov == 1 && (myboard.getpiece(destR, destC)->myplayer_->playernum_ != currplayer.playernum_)){
        validmove = true; 
    }
    //if not valid, return false 
    if(validmove == false){
        return false; 
    }


    //check that there's no other piece blocking you 
    //if move up, check nothing in way
    if(horizmov == 0){
        for(int i=1; i <= vertmov; i++){
            if(myboard.getpiece(srcR + i, srcC + i)->type_ != "**"){
                return false; 
            }
        }      
    }
    //if move diagonally, check only opponent piece in the way 
        //already checked in diangonal move validity check above 

    //all conditions met
    return true; 
};



bishop::bishop(player* currplayer){
    value_ = 3;
    if(currplayer -> playernum_ == 1){
        type_ = "wB";
    } 
    else{
        type_ = "bB";
    }
    myplayer_ = currplayer;
};

bishop::~bishop(){};

bool bishop::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC; 
    
    //check that the movement pattern is correct
    bool validmove = false; 
    //moving diagonally up-right
    if(vertmov > 0 && horizmov > 0 && (abs(vertmov) == abs(horizmov))){
        validmove = true; 
    }
    //moving diagonally up-left
    else if(vertmov > 0 && horizmov < 0 && (abs(vertmov) == abs(horizmov))){
        validmove = true; 
    }
    //moving diagonally down-left
    else if(vertmov < 0 && horizmov < 0 && (abs(vertmov) == abs(horizmov))){
        validmove = true; 
    }
    //moving diagonally down-right
    else if(vertmov < 0 && horizmov > 0 && (abs(vertmov) == abs(horizmov))){
        validmove = true; 
    }
    //if not valid, return false
    if(validmove == false){
        return false; 
    }

    //check that there's nothing blocking (whether it be your's or opponent's piece) exclusing the destination 
    //moving up-left
    if(vertmov > 0 && horizmov < 0){
        for(int i=1; i<vertmov; i++){
            if(myboard.getpiece(srcR + i, srcC - i)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving up-right
    else if(vertmov > 0 && horizmov > 0){
        for(int i=1; i<vertmov; i++){
            if(myboard.getpiece(srcR + i, srcC + i)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving down-right
    else if(vertmov < 0 && horizmov > 0){
        for(int i=1; i<horizmov; i++){
            if(myboard.getpiece(srcR - i, srcC + i)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving down-left
    else if(vertmov < 0 && horizmov < 0){
        for(int i=1; i<horizmov; i++){
            if(myboard.getpiece(srcR - i, srcC - i)->type_ != "**"){
                return false; 
            }
        }
    }
    //check that what's at the destination is an opposing piece (not your own piece that blocks)
    if(myboard.getpiece(destR, destC)->myplayer_->playernum_ == currplayer.playernum_){
        return false; 
    }

    //all conditions met
    return true; 
};



knight::knight(player* currplayer){
    value_ = 3;
    if(currplayer -> playernum_ == 1){
        type_ = "wK";
    } 
    else{
        type_ = "bK";
    }
    myplayer_ = currplayer;
};

knight::~knight(){}; 

bool knight::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC; 
    
    //check that the movement pattern is correct
    bool validmove = false; 
    //check move 2 vert and 1 horiz
    if(abs(vertmov) == 2 && abs(horizmov) == 1){
        validmove = true; 
    }
    else if(abs(vertmov) == 1 && abs(horizmov) == 2){
        validmove = true; 
    }
    //if not valid, return false
    if(validmove == false){
        return false; 
    }

    //check you don't have your own piece at the destination location 
    if(myboard.getpiece(destR, destC)->myplayer_->playernum_ == currplayer.playernum_){
        return false; 
    }
    
    //all conditions met
    return true; 
};



rook::rook(player* currplayer){
    value_ = 5;
    if(currplayer -> playernum_ == 1){
        type_ = "wR";
    } 
    else{
        type_ = "bR";
    }
    myplayer_ = currplayer;
};

rook::~rook(){}; 

bool rook::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC; 
    
    //check that movement pattern is correct 
    bool validmove = false; 
    //move vertically 
    if(horizmov == 0 && vertmov != 0){
        validmove = true; 
    }
    //move horizontally 
    else if(vertmov == 0 && horizmov != 0){
        validmove = true; 
    }
    //if not valid, return false
    if(validmove == false){
        return false; 
    }

    //check nothing blocking the piece to the destination, excluding the destination location 
    //moving up
    if(vertmov > 0 && horizmov == 0){
        for(int i=1; i<=vertmov; i++){
            if(myboard.getpiece(srcR + i, srcC)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving down 
    else if(vertmov < 0 && horizmov == 0){
        for(int i=-1; i>=vertmov; i--){
            if(myboard.getpiece(srcR + i, srcC)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving right
    if(vertmov == 0 && horizmov > 0){
        for(int i=1; i<=horizmov; i++){
            if(myboard.getpiece(srcR, srcC + i)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving left
    if(vertmov == 0 && horizmov < 0){
        for(int i=-1; i>=horizmov; i--){
            if(myboard.getpiece(srcR, srcC + i)->type_ != "**"){
                return false; 
            }
        }
    }
    //check you don't have your own piece at the destination location 
    if(myboard.getpiece(destR, destC)->myplayer_->playernum_ == currplayer.playernum_){
        return false; 
    }

    //all conditions met
    return true; 
};



queen::queen(player* currplayer){
    value_ = 9;
    if(currplayer -> playernum_ == 1){
        type_ = "wQ";
    } 
    else{
        type_ = "bQ";
    }
    myplayer_ = currplayer;
};

queen::~queen(){}; 

bool queen::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC; 

    //check that movement pattern is correct 
    bool validmove = false; 
    //move vertically 
    if(horizmov == 0 && vertmov != 0){
        validmove = true; 
    }
    //move horizontally 
    else if(vertmov == 0 && horizmov != 0){
        validmove = true; 
    }
    //moving diagonally up-right
    else if(vertmov > 0 && horizmov > 0 && (abs(vertmov) == abs(horizmov))){
        validmove = true; 
    }
    //moving diagonally up-left
    else if(vertmov > 0 && horizmov < 0 && (abs(vertmov) == abs(horizmov))){
        validmove = true; 
    }
    //moving diagonally down-left
    else if(vertmov < 0 && horizmov < 0 && (abs(vertmov) == abs(horizmov))){
        validmove = true; 
    }
    //moving diagonally down-right
    else if(vertmov < 0 && horizmov > 0 && (abs(vertmov) == abs(horizmov))){
        validmove = true; 
    }
    //if not valid, return false
    if(validmove == false){
        return false; 
    }

    //check that nothing's in way to destination, excluding destination
    //moving up-left
    if(vertmov > 0 && horizmov < 0){
        for(int i=1; i<vertmov; i++){
            if(myboard.getpiece(srcR + i, srcC - i)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving up-right
    else if(vertmov > 0 && horizmov > 0){
        for(int i=1; i<vertmov; i++){
            if(myboard.getpiece(srcR + i, srcC + i)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving down-right
    else if(vertmov < 0 && horizmov > 0){
        for(int i=1; i<horizmov; i++){
            if(myboard.getpiece(srcR - i, srcC + i)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving down-left
    else if(vertmov < 0 && horizmov < 0){
        for(int i=1; i<horizmov; i++){
            if(myboard.getpiece(srcR - i, srcC - i)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving up
    if(vertmov > 0 && horizmov == 0){
        for(int i=1; i<=vertmov; i++){
            if(myboard.getpiece(srcR + i, srcC)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving down 
    else if(vertmov < 0 && horizmov == 0){
        for(int i=-1; i>=vertmov; i--){
            if(myboard.getpiece(srcR + i, srcC)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving right
    if(vertmov == 0 && horizmov > 0){
        for(int i=1; i<=horizmov; i++){
            if(myboard.getpiece(srcR, srcC + i)->type_ != "**"){
                return false; 
            }
        }
    }
    //moving left
    if(vertmov == 0 && horizmov < 0){
        for(int i=-1; i>=horizmov; i--){
            if(myboard.getpiece(srcR, srcC + i)->type_ != "**"){
                return false; 
            }
        }
    }
    //check you don't have your own piece at the destination location 
    if(myboard.getpiece(destR, destC)->myplayer_->playernum_ == currplayer.playernum_){
        return false; 
    }

    //all conditions met
    return true; 
};



king::king(player* currplayer){
    value_ = -1; 
    if(currplayer -> playernum_ == 1){
        type_ = "wE";
    }
    else{
        type_ = "bE";
    }
    myplayer_ = currplayer;
};

king::~king(){}; 

bool king::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC; 

    //check that movement pattern is correct 
    bool validmove = false; 
    //move vertically 
    if(horizmov == 0 && (vertmov == 1 || vertmov == -1)){
        validmove = true; 
    }
    //move horizontally 
    else if(vertmov == 0 && (horizmov == 1 || horizmov == -1)){
        validmove = true; 
    }
    //move diagonally up-right or up-left
    else if(vertmov == 1 && (horizmov == 1 || horizmov == -1)){
        validmove = true; 
    }
    //move diagonally down-right or down-left
    else if(vertmov == -1 && (horizmov == 1 || horizmov == -1)){
        validmove = true; 
    }
    //if not valid, return false
    if(validmove == false){
        return false; 
    }

    //check you don't have your own piece at the destination location 
    if(myboard.getpiece(destR, destC)->myplayer_->playernum_ == currplayer.playernum_){
        return false; 
    }

    //all conditions met
    return true; 
};