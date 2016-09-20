

#include "../headers/Config.h"
#include "../headers/Move.h"
#include "../headers/Engine.h"



int main(int argv, char**argc)
{


	Game *game = init_board("chess.config");

	printf("INITIALIZATION\n");
       	print_board(game);	
	Node* N = init_node(game,NULL,NULL,NULL,NULL, GAME) ; 
	List * list = generate_all_boards(N,WHITE); 
//	print_list(N->next_level);
	Node* it = list->begin ; 

	while(it!=NULL ){
		generate_all_boards(it,WHITE); 
		it=it->next;

	}


	Tree* tree = init_tree(N);

	free_tree(tree); 

 







	
	check_memleak(); 







	return EXIT_SUCCESS;
}































