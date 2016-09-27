

#include "../headers/Config.h"
#include "../headers/Move.h"
#include "../headers/Engine.h"

//TODO : rename project

int main(int argv, char**argc)
{


//	Game *game = init_board("chess.config");
	Game* game = NULL ; 
        game= init_blank_game() ; 

	Node* N = init_node(game,NULL,NULL,NULL,NULL, GAME) ; 
	Tree* tree = generate_tree(N ,  4 , 20 , WHITE); 

	browse_tree(tree); 


	




	free_tree(tree); 

 	 






	
	check_memleak(); 






	return EXIT_SUCCESS;
}































