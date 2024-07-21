#include <iostream>
#include <cmath> 
#include <ostream> 
#include <vector> 
#include "header.h"
using namespace std; 

int main(){
    cout << "Starting Chess Game" << endl;  
    game mygame; //creates the players, identifies a current player, creates a board with pieces
    //board myboard; //creates the board, puts pieces on the board
    mygame.myboard_ -> print();  
     
    
    bool quit = false; 
    while(!quit){
        //player's turn to move a piece
        //get the player's inputs
        cout << "Please input the coordinates of your selected piece and your desired destination with column followed by row" << endl; 
        int srcC, srcR, destC, destR; 
        cin >> srcR >> srcC >> destR >> destC; 
        //check if user inputted board locations
        if(srcR > 7 || srcR < 0 || srcC > 7 || srcC < 0 ||destR > 7 || destR < 0 || destC > 7 || destC < 0){
            cout << "invalid entry, please enter a location on the board" << endl; 
            continue; 
        }
        if(mygame.validmove(srcR, srcC, destR, destC, *(mygame.myboard_), *(mygame.currplayer_))){ //function to check validity of the move
            mygame.movepiece(srcR, srcC, destR, destC, *(mygame.myboard_), *(mygame.currplayer_));//function to move the piece by swapping with what's in the correct space, also determines if need to take a piece
            if(mygame.checkwin()){ //function to check if there's a checkmate or draw 
                quit = true; 
            }
            mygame.nextplayer();//update the current player 
        }
        else{
            cout << "invalid move" << endl; 
            continue; 
        }
        
    }




    
    /*
    cout << "Player1's move" << endl; 
    int srcR, srcC, destR, destC; 
    cin >> srcR >> srcC >> destR >> destC; //get source piece and destination location 
    mygame.myboard_.movepiece(srcC, srcR).
    */

    return 0; 
}