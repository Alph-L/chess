#ifndef MYHEADER_header
#define MYHEADER_header

#include <vector> 

class piece; 
class player{
public: 
    player(); 
    player(int playernum);
    void printstats(); 
    int score_; 
    int nummoves_; 
    int playernum_; 
    std::vector<piece*> fallen; 
};

class board; 
class piece{
public: 
    piece(); 
    virtual ~piece(); 
    
    friend std::ostream& operator<<(std::ostream& os, const piece& p);
    virtual bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer) = 0;
    
    int value_;
    std::string type_; 

    player *myplayer_; 
};

class blankpiece: public piece{
public: 
    blankpiece(); 
    ~blankpiece(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer); 
};

class pawn: public piece{
public:
    pawn(player* currplayer); 
    ~pawn(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer);
private: 
    bool moved_; 
};

class bishop: public piece{
public:
    bishop(player* currplayer); 
    ~bishop(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer);
};

class knight: public piece{
public:
   knight(player* currplayer); 
   ~knight(); 
   bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer);
};

class rook: public piece{
public:
    rook(player* currplayer);
    ~rook();  
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer);
};

class queen: public piece{
public:
    queen(player* currplayer);
    ~queen();  
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer);
};

class king: public piece{
public:
    king(player* currplayer); 
    ~king(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer);
};




class board{
public: 
    //constructor: create boards and initialize pieces 
    board(player* p1, player* p2); 
    //destructor: destroy boards
    ~board(); 
    //print board
    void print(); 
    //get piece from the board at a certain location
    piece* getpiece(int srcR, int srcC);
    //actual board
    piece*** visualboard_;
};


class game{
public: 
    game(); 
    bool validmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer);
    void movepiece(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer); 
    bool checkwin(); 
    void nextplayer();   

    player* currplayer_;
    player* player1_; 
    player* player2_;  
    board* myboard_; 
};





#endif 