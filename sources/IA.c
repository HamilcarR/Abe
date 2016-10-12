#include "../headers/IA.h"
/***************************************************************************************************************************************************************/
static inline Best_Move max(List* L){
	assert(L != NULL); 
	Node* iterator = L->begin ; 
	int max = -INT32_MAX ; 
	Node* max_n = L->begin ;
	while(iterator != NULL){
		
		if(max<=iterator->min_max){
			max = iterator->min_max;
			max_n = iterator ; 	
		}

		iterator=iterator->next;
	}

	return (Best_Move) { .node = max_n , .score = max}; 
}


static inline Best_Move min(List* L){
	assert(L != NULL); 
	Node* iterator = L->begin ; 
	int min = INT32_MAX ; 
	Node* min_n = L->begin; 
	while(iterator != NULL){
		
		if(min>=iterator->min_max){
			
			min = iterator->min_max;
			min_n = iterator ; 
		}
		iterator=iterator->next;
	}

	

	return (Best_Move) { .node = min_n , .score = min}; 
}






void init_tree_minmax(Node* root){
	assert(root->data_type == GAME); 
	Game* game = root->value; 
	if(root->next_level!= NULL){
		Node* it = root->next_level->begin ;
	        	
		while(it!=NULL){
		
			init_tree_minmax(it); 
			it=it->next; 

		}

		if(game->turn==BLACK){
		//	root->min_max = min(root->next_level);
			Best_Move M = min(root->next_level);
			root->min_max = M.score ;
		//	        printf("score MIN : %i\n",M.score);	
		}
		else{
			Best_Move M = max(root->next_level);
			root->min_max = M.score; 
	
		  //      printf("score MAX : %i\n",M.score);	
			//	root->min_max = max(root->next_level);
		}



	}
	else if(root->next_level == NULL || finished_game(root->value))
		root->min_max=(game->turn == MIN)? -game->score_black : game->score_white ; 

	


}






void initialize_minmax(Tree* tree ){
	assert(tree != NULL);
	assert(tree->root!=NULL);	
	
	init_tree_minmax(tree->root);


}












/***************************************************************************************************************************************************************/












/***************************************************************************************************************************************************************/

Node* get_opt_move(Node* it){
	assert(it->data_type == GAME);
	Game* game = it->value ;
        init_tree_minmax(it); 	
	if(it->next_level!=NULL){
		if(game->turn == MAX)
			return max(it->next_level).node ; 
		else
			return min(it->next_level).node ; 
	}
	else{
		printf(" next level null \n");
		return it ; 

	}

}
//TODO complete





















/***************************************************************************************************************************************************************/


