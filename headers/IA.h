#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED


#include "Engine.h"
/* Path finding,MINIMAX etc...*/


enum MINMAX {MIN = BLACK , MAX = WHITE};
typedef enum MINMAX MINMAX ; 


typedef struct{
	Node* node ; 
	int score ; 



}Best_Move;





void initialize_minmax(Tree* t);
Node* get_opt_move(Node* it) ; 





 

 
  















#endif 
