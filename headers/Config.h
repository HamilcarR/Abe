#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "Consts.h"



/**
 *\file config.h

 *\brief program's I/O system and initialization.


 *this header is about setting up the game,reading any state of it,saving,and check for any error in pieces positions.

*/




struct Stack;
struct Position;
struct Game;
struct Player;



/**
 \file config.h
 \struct Position Config.h
 \brief structure of positions
 *x and y are clamped between 0 and 7,to represent to position of a piece on the board.

 */

typedef struct  {
    int8_t x;
    int8_t y;

}Position;

/**
 \file config.h
 \struct Piece Config.h
 \brief Piece struct
 *

 */

typedef struct {
    Type type ;
    COLOR color ;
    Position position ;
}Piece;

/**
 \file config.h
 \struct Stack Config.h
 \brief Stack struct
 *The dead pieces.

 */

typedef struct{
    Type *type;
    COLOR *color;
    size_t number;
}Stack;

/**
    \file Config.h
    \brief structure of a player
    \struct Player Config.h
    *\var player_type
    *
    *
    */
typedef struct {
    COLOR player_type ;
    Piece** pieces; // array of pointers on pieces
    size_t *stack[MAX_PIECES]; //pointer to Game::stack
    size_t number;
}Player;



typedef struct {
    COLOR color_distrib[BOARD_SIZE][BOARD_SIZE]; /*size 8x8 */
    Piece * pieces; //array of Pieces
    size_t stack [MAX_PIECES] ; /*size 12*/
    size_t pieces_size ;
    COLOR turn ; 
}Game;









/* Load a chess game from a file,structured as such :
-STACK :
  W B       // white pieces killed
  W C       // C is a knight,K is a king etc
  W C

  B C   // black pieces killed


-PARAMETERS :
* W P 6 7   //white pawn at x = 6 ; y = 7
* B K 0 1   //black king at x = 0 ; y = 1

*/

 void free_game(Game * game); //free the game struct
 void free_player(Player *player) ;
 void free_position(Position *position) ;
 void print_board(Game* game);
 void read_pieces(Game* game);
Game* init_blank_game(); 
Game * get_board_copy(Game* src); //get a cpy from src.
Game * init_board(const char* filename); //initialize the board from a file, mid game ,or end game
void save_board(const char * filename); // save the current game on the file "filename"
ERROR check_for_errors(); //check for misplaced pieces ,wrong initialization parameters etc ...
uint8_t get_pieceID(Piece piece);//return a piece identifier from the type and color of the piece
void add_to_array(Piece* piece, int size, Piece P);

bool check_valid_position(Position pos);
void print_piece(Piece* p);

bool equal_game(Game* g1 , Game* g2) ; 
bool equal_piece(Piece *p1,Piece *p2) ; 








#endif
