#include <iostream> 
#include "header.h"
using namespace std; 

board::board(){
    //initilize the board with pieces
    //add blanks
    for(int i=2; i<6; i++){ 
        for(int j=0; j<8; j++){
            board_[i][j] = new blankpiece(); 
        }
    }
    //add pawns
    for(int i=0; i<8; i++){ 
        board_[1][i] = new pawn('w'); 
        board_[6][i] = new pawn('b'); 
    }
    //add rooks
    board_[0][0] = new rook('w'); 
    board_[0][7] = new rook('w'); 
    board_[7][0] = new rook('b'); 
    board_[7][7] = new rook('b'); 
    //add knights
    board_[0][1] = new knight('w'); 
    board_[0][6] = new knight('w'); 
    board_[7][1] = new knight('b'); 
    board_[7][6] = new knight('b'); 
    //add bishops
    board_[0][2] = new bishop('w'); 
    board_[0][5] = new bishop('w'); 
    board_[7][2] = new bishop('b'); 
    board_[7][5] = new bishop('b'); 
    //add queens
    board_[0][3] = new queen('w'); 
    board_[7][3] = new queen('b'); 
    //add kings
    board_[0][4] = new king('w'); 
    board_[7][4] = new king('b'); 
}

board::~board(){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            delete board_[i][j]; 
        }
    }
}

void board::print(){
    for(int i=7; i>=0; i--){
        cout << i+1 << " "; 
        for(int j=0; j<8; j++){
            cout << board_[i][j] << " "; 
        }
        cout << endl; 
    }
    cout << "  "; 
    for(int i=0; i<8; i++){
        char ind = 'A' + i; 
        cout << ind << "  ";
    }
    cout << endl; 
}

ostream& operator<<(ostream& os, const piece* p){
    os << p -> type_; 
    return os; 
};

piece* board::getpiece(int srcR, int srcC){
    return board_[srcR][srcC]; 
}; 

void board::replace(int destR, int destC, string type, player& currplayer){
    delete board_[destR][destC]; 
    if(type == "blank"){
        board_[destR][destC] = new blankpiece(); 
    }
    else if(type == "pawn"){
        board_[destR][destC] = new pawn(currplayer.getid()); 
    }
    else if(type == "bishop"){
        board_[destR][destC] = new bishop(currplayer.getid()); 
    }
    else if(type == "knight"){
        board_[destR][destC] = new knight(currplayer.getid()); 
    }
    else if(type == "rook"){
        board_[destR][destC] = new rook(currplayer.getid()); 
    }
    else if(type == "queen"){
        board_[destR][destC] = new queen(currplayer.getid()); 
    }
}; 

void board::swap(int srcR, int srcC, int destR, int destC){
    piece* tmp = board_[destR][destC]; 
    board_[destR][destC] = board_[srcR][srcC]; 
    board_[srcR][srcC] = tmp; 
};