#include <iostream> 
#include "header.h"
using namespace std; 

piece::piece(){
    value_ = -1; 
    type_ = "null";
    owner_ = 'n';
}; 

piece::~piece(){}; 

char piece::getowner(){
    return owner_; 
};

string piece::gettype(){
    return type_; 
}

int piece::getvalue(){
    return value_; 
}

bool piece::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    return true; 
};

blankpiece::blankpiece(){
    value_ = 0; 
    type_ = "**";
    owner_ = 'n';
}; 

blankpiece::~blankpiece(){}; 

bool blankpiece::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    return true; 
}

pawn::pawn(){
    value_ = 1; 
    type_ = "P"; 
    owner_ = 'n'; 
}; 

pawn::pawn(char id){
    value_ = 1; 
    if(id == 'w'){
        type_ = "wP"; 
    }
    else{
        type_ = "bP"; 
    }
    owner_ = id; 
    moved_ = false; 
}; 

pawn::~pawn(){};

bool pawn::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    //cout << "TEST PAWN CHECKMOVE" << endl; 
    
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC;

    //check pattern correctness for white and nothing blocking
    if(owner_ == 'w'){
        if(vertmov == 1 && (horizmov == 1 || horizmov == -1) && myboard.getpiece(destR, destC)->getowner() == 'b'){
            return true; 
        }
        else if(moved_ == false && horizmov == 0 && (vertmov == 2 || vertmov == 1)){
            if(vertmov == 2){
                if(myboard.getpiece(srcR + 1, srcC + 1)->getowner() == 'n' && myboard.getpiece(srcR + 2, srcC + 2)->getowner() == 'n'){
                    return true; 
                }
            }
            else if(vertmov == 1){
                if(myboard.getpiece(srcR + 1, srcC + 1)->getowner() == 'n'){
                    return true; 
                }
            }
        }
        else if(moved_ == true && horizmov == 0 && vertmov == 1){
            if(vertmov == 1){
                if(myboard.getpiece(srcR + 1, srcC + 1)->getowner() == 'n'){
                    return true; 
                }
            }
        }  
    }
    //check for black 
    else if(owner_ == 'b'){
        if(vertmov == -1 && (horizmov == 1 || horizmov == -1) && myboard.getpiece(destR, destC)->getowner() == 'w'){
            return true; 
        }
        else if(moved_ == false && horizmov == 0 && (vertmov == -2 || vertmov == -1)){
            if(vertmov == -2){
                if(myboard.getpiece(srcR - 1, srcC - 1)->getowner() == 'n' && myboard.getpiece(srcR - 2, srcC - 2)->getowner() == 'n'){
                    return true; 
                }
            }
            else if(vertmov == -1){
                if(myboard.getpiece(srcR - 1, srcC - 1)->getowner() == 'n'){
                    return true; 
                }
            }
        }
        else if(moved_ == true && horizmov == 0 && vertmov == -1){
            if(vertmov == -1){
                if(myboard.getpiece(srcR - 1, srcC - 1)->getowner() == 'n'){
                    return true; 
                }
            } 
        }  
    }

    //either no pattern matched, or something is blocking the pieces, invalid input 
    return false; 
}

bishop::bishop(){
    value_ = 3; 
    type_ = "B"; 
    owner_ = 'n'; 
}; 

bishop::bishop(char id){
    value_ = 3; 
    if(id == 'w'){
        type_ = "wB"; 
    }
    else{
        type_ = "bB"; 
    }
    owner_ = id; 
}; 

bishop::~bishop(){};

bool bishop::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC; 

    if(abs(vertmov / horizmov) == 1 && ((vertmov > 0 && horizmov < 0)||(vertmov > 0 && horizmov > 0)||(vertmov < 0 && horizmov < 0)||(vertmov < 0 && horizmov > 0))){ //check the pattern 
        if(vertmov > 0 && horizmov < 0){ //up-left 
            for(int i=1; i<vertmov; i++){ //excluding destination, nothing in the way 
                if(myboard.getpiece(srcR + i, srcC - i)->getowner() != 'n'){
                    return false; 
                }
            }
            if(myboard.getpiece(destR, destC)->getowner() == currplayer.getid()){ //at destination, can't be own piece
                return false; 
            }
        }
        else if(vertmov > 0 && horizmov > 0){ //up-right
            for(int i=1; i<vertmov; i++){ //excluding destination, nothing in the way 
                if(myboard.getpiece(srcR + i, srcC + i)->getowner() != 'n'){
                    return false; 
                }
            }
            if(myboard.getpiece(destR, destC)->getowner() == currplayer.getid()){ //at destination, can't be own piece
                return false; 
            }
        }
        else if(vertmov < 0 && horizmov < 0){ //down-left
            for(int i=1; i<abs(vertmov); i++){ //excluding destination, nothing in the way 
                if(myboard.getpiece(srcR - i, srcC - i)->getowner() != 'n'){
                    return false; 
                }
            }
            if(myboard.getpiece(destR, destC)->getowner() == currplayer.getid()){ //at destination, can't be own piece
                return false; 
            }
        }
        else if(vertmov < 0 && horizmov > 0){ //down-right
            for(int i=1; i<abs(vertmov); i++){ //excluding destination, nothing in the way 
                if(myboard.getpiece(srcR - i, srcC + i)->getowner() != 'n'){
                    return false; 
                }
            }
            if(myboard.getpiece(destR, destC)->getowner() == currplayer.getid()){ //at destination, can't be own piece
                return false; 
            }
        }
        //nothing blocking, and pattern matched, valid 
        return true; 
    } 
    else{
        return false; 
    }
};

knight::knight(){
    value_ = 3; 
    type_ = "H"; 
    owner_ = 'n'; 
}; 

knight::knight(char id){
    value_ = 3; 
    if(id == 'w'){
        type_ = "wH"; 
    }
    else{
        type_ = "bH"; 
    }
    owner_ = id; 
}; 

knight::~knight(){};

bool knight::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC; 

    if(((vertmov == 2 || vertmov == -2) && (horizmov == 1 || horizmov == -1)) || ((vertmov == 1 || vertmov == -1) && (horizmov == 2 || horizmov == -2))){
        if(myboard.getpiece(destR, destC)->getowner() != currplayer.getid()){
            return true; 
        }
    }
    return false; 
};

rook::rook(){
    value_ = 5; 
    type_ = "R"; 
    owner_ = 'n'; 
}; 

rook::rook(char id){
    value_ = 5; 
    if(id == 'w'){
        type_ = "wR"; 
    }
    else{
        type_ = "bR"; 
    }
    owner_ = id; 
}; 

rook::~rook(){}; 

bool rook::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC; 

    if(((vertmov > 0 || vertmov < 0) && horizmov == 0) || (vertmov == 0 && (horizmov > 0 || horizmov < 0))){
        //check for anything blocking 
        if(vertmov > 0){ //up
            for(int i=1; i<vertmov; i++){ //excluding destination, nothing in the way 
                if(myboard.getpiece(srcR + i, srcC)->getowner() != 'n'){
                    return false; 
                }
            } 
        }
        else if(vertmov < 0){ // down 
            for(int i=1; i<abs(vertmov); i++){ //excluding destination, nothing in the way 
                if(myboard.getpiece(srcR - i, srcC)->getowner() != 'n'){
                    return false; 
                }
            } 
        }
        else if(horizmov > 0){ // right 
            for(int i=1; i<horizmov; i++){ //excluding destination, nothing in the way 
                if(myboard.getpiece(srcR, srcC + i)->getowner() != 'n'){
                    return false; 
                }
            } 
        }
        else if(horizmov < 0){ //left
            for(int i=1; i<abs(horizmov); i++){ //excluding destination, nothing in the way 
                if(myboard.getpiece(srcR, srcC - i)->getowner() != 'n'){
                    return false; 
                }
            } 
        }
        if(myboard.getpiece(destR, destC)->getowner() == currplayer.getid()){ //at destination, can't be own piece
            return false; 
        }

        //pattern matched, nothing blocking
        return true; 
    }
    //pattern not matched
    return false;
};

queen::queen(){
    value_ = 9; 
    type_ = "Q"; 
    owner_ = 'n'; 
}; 

queen::queen(char id): b_(id), r_(id){
    value_ = 9; 
    if(id == 'w'){
        type_ = "wQ"; 
    }
    else{
        type_ = "bQ"; 
    }
    owner_ = id; 
}; 

queen::~queen(){}; 

bool queen::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    if(b_.checkmove(srcR, srcC, destR, destC, myboard, currplayer) || r_.checkmove(srcR, srcC, destR, destC, myboard, currplayer)){
        return true; 
    }
    else{
        return false; 
    }
};

king::king(){
    value_ = 100; 
    type_ = "K"; 
    owner_ = 'n'; 
}; 

king::king(char id): b_(id), r_(id) {
    value_ = 100; 
    if(id == 'w'){
        type_ = "wK"; 
    }
    else{
        type_ = "bK"; 
    }
    owner_ = id; 
}; 

king::~king(){}; 

bool king::checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer){
    int vertmov = destR - srcR; 
    int horizmov = destC - srcC; 

    if((abs(vertmov) == abs(horizmov) == 1) || (horizmov == 0 && (vertmov == 1 || vertmov == -1)) || (vertmov == 0 && (horizmov == 1 || horizmov == -1))){
        if(b_.checkmove(srcR, srcC, destR, destC, myboard, currplayer) || r_.checkmove(srcR, srcC, destR, destC, myboard, currplayer)){
            return true; 
        }
    }
    return false; 
};