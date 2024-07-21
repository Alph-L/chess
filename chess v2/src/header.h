#pragma once 
#include <iostream> 
#include <vector> 

class board; 
class player; 
class piece{ //each piece has a value, named type, and an owner
public: 
    piece(); 
    virtual ~piece(); 
    std::string gettype(); 
    char getowner(); 
    int getvalue(); 
    friend std::ostream& operator<<(std::ostream& os, const piece* p);
    virtual bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer);
protected: 
    int value_; 
    std::string type_; 
    char owner_; 
}; 

class blankpiece: public piece{
public: 
    blankpiece(); 
    ~blankpiece(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer);
private:
}; 

class pawn: public piece{
public: 
    pawn();
    pawn(char id); 
    ~pawn(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer); //check the move follows the piece pattern and nothing block
private:
    bool moved_; 
}; 

class bishop: public piece{
public: 
    bishop();
    bishop(char id);  
    ~bishop(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer); //check the move follows the piece pattern and nothing block
private:
}; 

class knight: public piece{
public:
    knight(); 
    knight(char id); 
    ~knight();  
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer); //check the move follows the piece pattern and nothing block
private:
}; 

class rook: public piece{
public: 
    rook(); 
    rook(char id); 
    ~rook(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer); //check the move follows the piece pattern and nothing block
private:
}; 

class queen: public piece{
public: 
    queen(); 
    queen(char id); 
    ~queen(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer); //check the move follows the piece pattern and nothing block
private:
    bishop b_; 
    rook r_; 
}; 

class king: public piece{
public: 
    king(); 
    king(char id); 
    ~king(); 
    bool checkmove(int srcR, int srcC, int destR, int destC, board& myboard, player& currplayer); //check the move follows the piece pattern and nothing block
private:
    bishop b_; 
    rook r_; 
}; 

class player{ //has score, number moves, list pieces taken, name identifier
public: 
    player();  
    player(char id); 
    ~player(); 
    char getid(); 
    void addscore(int add);
    std::vector<piece*> taken;
private: 
    int score_; 
    int nummoves_; 
    char id_; 
}; 

class board{ //has pieces 
public: 
    board(); 
    ~board(); 
    void print(); 
    piece* getpiece(int srcR, int srcC); 
    void replace(int destR, int destC, std::string type, player& currplayer);
    void swap(int srcR, int srcC, int destR, int destC);
private: 
    piece* board_[8][8];
}; 

class game{ //has a board and players (white/w and black/b)
public: 
    game(); 
    ~game(); 
    bool validmove(int srcR, int srcC, int destR, int destC); 
    void swap(int srcR, int srcC, int destR, int destC);
    void nextplayer(); 
    bool checkwin(); 
    board* getboard(); 
    player* getcurrplayer(); 
private: 
    board* myboard_; 
    player* white_; 
    player* black_; 
    player* currplayer_; 
};