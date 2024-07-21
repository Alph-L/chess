#include <iostream>
#include <cmath> 
#include <ostream> 
#include <vector> 
#include "header.h"
using namespace std; 

board::board(player* p1, player* p2){
    //dynamically allocate 2d array of pointers to pieces
    visualboard_ = new piece**[8];

    for(int i=0; i<8; i++){
        visualboard_[i] = new piece*[8]; 
    }

    //initialize with all blank pieces 
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            visualboard_[i][j] = new blankpiece(); 
        }
    }
    
    //initialize the board with players' pieces
    //add pawns
    for(int i=0; i<8; i++){ 
        visualboard_[1][i] = new pawn(p1); 
        visualboard_[6][i] = new pawn(p2); 
    }
    //add rooks
    visualboard_[0][0] = new rook(p1); 
    visualboard_[0][7] = new rook(p1); 
    visualboard_[7][0] = new rook(p2); 
    visualboard_[7][7] = new rook(p2); 
    //add knights
    visualboard_[0][1] = new knight(p1); 
    visualboard_[0][6] = new knight(p1); 
    visualboard_[7][1] = new knight(p2); 
    visualboard_[7][6] = new knight(p2); 
    //add bishops
    visualboard_[0][2] = new bishop(p1); 
    visualboard_[0][5] = new bishop(p1); 
    visualboard_[7][2] = new bishop(p2); 
    visualboard_[7][5] = new bishop(p2); 
    //add queens
    visualboard_[0][3] = new queen(p1); 
    visualboard_[7][4] = new queen(p2); 
    //add kings
    visualboard_[0][4] = new king(p1); 
    visualboard_[7][3] = new king(p2); 
};

board::~board(){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            delete visualboard_[i][j];
        }
        delete [] visualboard_[i];
    }
    delete [] visualboard_; 
};

void board::print(){
    //start printing from the top left of the board
    for(int i=7; i>=0; i--){
        for(int j=0; j<8; j++){
            cout << *visualboard_[i][j] << " "; 
        }
        cout << endl; 
    }
};

ostream& operator<<(ostream& os, const piece& p){
    os << p.type_; 
    return os; 
};

piece* board::getpiece(int srcR, int srcC){
    return visualboard_[srcR][srcC];
};
