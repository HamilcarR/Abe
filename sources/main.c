

#include "../headers/Config.h"
#include "../headers/Move.h"
#include "../headers/Engine.h"



int main(int argv, char**argc)
{


	Game *game = init_board("chess.config");


	Node* N = init_node(game,NULL,NULL,NULL,NULL, GAME) ; 
//	auto width = atoi(argc[1]) , depth = atoi(argc[2]); 
	Tree* tree = generate_tree(N ,  6  , 3 , WHITE); 

	browse_tree(tree); 


	




	free_tree(tree); 

 	 







	
	check_memleak(); 







	return EXIT_SUCCESS;
}































