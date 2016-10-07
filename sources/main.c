

#include "../headers/Config.h"
#include "../headers/Move.h"
#include "../headers/Engine.h"
#include <pthread.h>
//TODO : rename project


 const uint8_t D = 2 ; 
 const uint8_t W = 200 ; 



int main(int argv, char**argc)
{


	Game *games = init_board("chess.config");
	Node *M = init_node(games , NULL , NULL , NULL,NULL,GAME); 
	Game* game = NULL ; 
        game= init_blank_game() ; 

	Node* N = init_node(game,NULL,NULL,NULL,NULL, GAME) ; 
	Tree* tree = generate_tree(N , D ,W, WHITE); 
	Tree **ptr_tree = &tree; 

	 
	//browse_tree(ptr_tree); 
	free_tree(*ptr_tree); 
	check_memleak(); 
	destroy_mutex(); 
	pthread_exit(NULL);

	return EXIT_SUCCESS;
}































