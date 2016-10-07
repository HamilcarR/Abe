#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED
#include "mmanager.h"
 





 enum GLOBAL_CONSTS { MAX_PIECES = 12 , BOARD_SIZE = 8 } ; 
typedef enum GLOBAL_CONSTS GLOBAL_CONSTS ; 


/*pieces identifiers*/
 enum PIECES_TYPE  { PAWN_WHITE = 0
, KNIGHT_WHITE=1
, ROOK_WHITE= 2
, BISHOP_WHITE= 3
, KING_WHITE= 4
, QUEEN_WHITE= 5
, PAWN_BLACK= 6
, KNIGHT_BLACK= 7
, ROOK_BLACK= 8
, BISHOP_BLACK= 9
, KING_BLACK= 10
, QUEEN_BLACK= 11
};
typedef enum PIECES_TYPE PIECES_TYPE ; 


/** \file Consts.h
    \brief all enums and constants

    *declare some useful constants
    */

/**
    \file Consts.h
    \brief definition of a boolean
    \enum bool

    *true for 1 , false for 0
    */

enum bool {true = 1 , false = 0 };
typedef enum bool bool ;


extern const uint8_t MAX_PAWN    ;
extern const uint8_t MAX_KING    ;
extern const uint8_t MAX_QUEEN   ;
extern const uint8_t MAX_ROOK    ;
extern const uint8_t MAX_KNIGHT  ;
extern const uint8_t MAX_BISHOP  ;


/**
    \file Consts.h
    \brief Color enumeration
    \enum COLOR

    * Enumerate the two colors of the game.
    * 0 for white , 1 for black
    */
enum COLOR {WHITE = 0 ,BLACK = 1};
typedef enum COLOR COLOR ;

/**\file Consts.h
    \brief Chess pieces enumeration
    \enum Type
    *The differents pieces of a chess game
    */
enum Type {PAWN = 0 ,KING = 1 ,QUEEN = 2,ROOK = 3 ,KNIGHT=4 ,BISHOP = 5};
typedef enum Type Type;

enum ERROR {OKAY = 0 , WRONG_SIZE_BOARD = -1 ,GAME_FINISHED = -2 , PIECES_ON_SAME_POSITION=-3 ,BAD_PIECE_LOCATION = -4 , WRONG_MOVE = -5 , NOT_ENEMY = -6 }; //TODO : fill up
typedef enum ERROR ERROR ;


 static const char* piece_name[] = {
    "white pawn" ,
    "white knight" ,
    "white rook" ,
    "white bishop" ,
    "white king",
    "white queen",
    "black pawn",
    "black knight",
    "black rook",
    "black bishop",
    "black king",
    "black queen"

    };






static const int8_t POSERR= -1; /*Piece position error,if any coordinate of any pieces is corrupted or off-bounds*/
static const int8_t POSINIT= -2 ;


  








#endif // CONSTS_H_INCLUDED
