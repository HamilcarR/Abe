#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED
#include "Consts.h"
#include "Config.h"

 typedef struct{
    Position *position ; /*array of different moves*/
    size_t number; /*number of moves*/
}Moves;


/*move a piece on the board...returns an ERROR if it's a wrong move,or out of bounds */
void kill(Piece** piece, Game* game, int j);

Moves move_pawn(Game *game,Piece *piece);
Moves move_king(Game *game,Piece *piece);
Moves move_queen(Game *game,Piece *piece);
Moves move_knight(Game *game,Piece *piece);
Moves move_rook(Game *game,Piece *piece);
Moves move_bishop(Game *game,Piece *piece);
 Piece* select_piece(Game *game,Position pos);
ERROR move_piece(Game* ,Piece**,Position);
/*if two pieces are the same*/
bool equal_pieces(Piece *piece1 , Piece * piece2);
Moves generate_moves(Game* , Piece**) ; 
extern bool finished_game(Game* g) ; 
#endif // MOVE_H_INCLUDED
