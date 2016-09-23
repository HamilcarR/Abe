

#include "../headers/Config.h"
#include "../headers/Move.h"
#include "../headers/Engine.h"



int main(int argv, char**argc)
{


	Game *game = init_board("chess.config");


	Node* N = init_node(game,NULL,NULL,NULL,NULL, GAME) ; 
	Tree* tree = generate_tree(N ,  4  , 10 , WHITE); 

	browse_tree(tree); 


	




	free_tree(tree); 

 	 







	
	check_memleak(); 







	return EXIT_SUCCESS;
}































