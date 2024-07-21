#include <iostream> 
#include "header.h"
using namespace std; 

int main(){
    cout << "Starting Chess game" << endl; 
    game mygame; 
    mygame.getboard()->print(); //print starting board

    bool quit = false; 
    while(quit == false){
        //get user inputs
        cout << "Please input the coordinates of your selected piece and your desired destination with column followed by row" << endl; 
        int srcC, srcR, destC, destR; 
        char isrcC, idestC;
        cin >> isrcC >> srcR >> idestC >> destR; 

        srcC = isrcC - 'A'; 
        destC = idestC - 'A';
        srcR -= 1; 
        destR -= 1; 
    

        if(srcC == -1){
            cout << "Forfeited" << endl; 
            break; 
        }

        //check input validity 
        if(!mygame.validmove(srcR, srcC, destR, destC)){
            cout << "Invalid input" << endl; 
            continue; 
        }
        
        //swap the pieces, take if necessary, and add scores if necessary
        mygame.swap(srcR, srcC, destR, destC);

        //print the board
        mygame.getboard()->print();

        //check win 
        if(mygame.checkwin()){
            cout << "Winner is " << mygame.getcurrplayer() -> getid() << endl; 
            break; 
        } 

        //swap player
        mygame.nextplayer(); 
        
    }

    return 0; 
}