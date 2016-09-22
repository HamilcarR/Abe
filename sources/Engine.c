#include "../headers/Engine.h"
/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/



Node * init_node(void* data, Node* next, Node* prev,List* next_lvl,Node* prev_lvl,N_DATA type){
	Node *node = calloc(1,sizeof(Node));
	MEMALLOC_DEBUG_NODE++; 
	node->data_type = type ; 
	node->value = data ; 
	node->next = next ; 
	node->prev = prev ; 
	node->prev_level = prev_lvl ; 
	node->next_level = next_lvl ; 

	return node ; 







}



/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/





void free_node(Node * node) {
	switch(node->data_type){
		case GAME :

		free_game((Game*) (node->value)) ; 

		node->value = NULL ; 
		break;

		case ALLOC_PTR : 
		free(node->value) ; 

		node->value = NULL ; 
		break ; 
		
		default :
		node->value = NULL ; 

		break; 

		}


	MEMDEALLOC_DEBUG_NODE++; 	
	free(node) ; 



}



/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
void free_list(List* list){

Node *i=list->begin ; 
while(i!=NULL){
	Node *temp = i;
        i = i->next; 	
	free_node(temp);
	
}
MEMDEALLOC_DEBUG_LIST++ ; 
free(list) ; 

}











/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/


static size_t DEBUG_COUNTER = 0 ; 

static void free_tree_nodes(Node* root){ 

	

	//IMPORTANT : I HATE RECURSION.
	if(root->next_level != NULL && root->next_level->begin != NULL){
		Node* iterator = root->next_level->begin ; 
			
		

		while(iterator!=NULL){
			Node *temp = iterator ;	
			iterator=iterator->next;
			free_tree_nodes(temp);
			
		
		}
		MEMDEALLOC_DEBUG_LIST++; 
		free(root->next_level) ; 


	}

	
	free_node(root);


}

void free_tree(Tree* tree){
	DEBUG_COUNTER = 0 ;
        
	free_tree_nodes(tree->root) ;
	MEMDEALLOC_DEBUG_TREE++;
	free(tree);



}


Tree* init_tree(Node* root){
	Tree* tree = calloc(1,sizeof(Tree));
	MEMALLOC_DEBUG_TREE++;
         	
	tree->root = root; 

	return tree ; 


}
















/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

List* init_list(Node* begin){

	

List* list ; 
list = malloc(sizeof(List)) ;
MEMALLOC_DEBUG_LIST++;
list->count = 1 ; 
list->data_type=begin->data_type;
list->begin = begin ; 
list->end = begin ; 
return list ; 

}







/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/





void add_node_to_list(List* list , Node* node) {
			if(list->count == 0 ){
				list->begin = node ; 
				list->end = node ;
				list->count++ ; 
				return ;
			}	
		 	node->prev_level =(list->begin)->prev_level;
		 	node->next_level =(list->begin)->next_level; 	
		 	node->prev = list->end ; 
		  	(list->end)->next = node;
	  	  	list->end = node ; 	  
		  	node->next = NULL ;
		  	list->count++;
		
}














/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/





void print_list(List *list){


	if(list->data_type == GAME){	
		Node * it ;
		for(it=list->begin; it != NULL ; it = it->next){
			printf("\n Node address : %p\n" , it); 
			print_board((Game*)(it->value)); 	


		}

	}

	
	else if (list->data_type == STRING){
		Node * it ;
		for(it=list->begin; it != NULL ; it = it->next)
			printf("%s" ,(char*) (it->value)); 
		
	}

	
	



	printf("\n List size is : %i\n",list->count);



}

















/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/


List* init_empty_list(N_DATA data){
	List* liste = calloc( 1 , sizeof(List));
	MEMALLOC_DEBUG_LIST++ ; 
	liste->count = 0 ; 
	liste->begin = NULL ; 
	liste->end = NULL ;
	liste->data_type = data ; 
	return liste ; 



}









/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/


static Node* new_piece_location(Position pos , Node * game , size_t pieceID){
	Game* board = get_board_copy(  game->value ); 
	Piece* ptr=&(board->pieces[pieceID]) , **ptr2nd = &ptr;
	move_piece(board,ptr2nd,pos);

	Node* P =  init_node(board,NULL,NULL,NULL,NULL,GAME); 
	return P ; 

}


/*generate all combinations of pieceID and return them as a linked list */
List* generate_boards(Node* game,uint16_t width , size_t pieceID){
	if(game->data_type != GAME){ 
		
		free_node(game);
		return NULL ; 

	}
	List* list ; 
	list = init_empty_list(GAME) ; 	
	
	Game * data =(Game*) game->value ;



	Piece* p = &(data->pieces[pieceID]);
	Piece** pp = &p ; 
	Moves moves = generate_moves(data, pp);
	int siz = (moves.number<=width) ? moves.number : width; 	
	for(int i = 0 ; i < siz ; i ++ ){
		Node* P = new_piece_location(moves.position[i] , game , pieceID);/*TODO complete */ 
		add_node_to_list(list , P ) ; 
		

	}
	MEMDEALLOC_DEBUG_POSITION++;
        free(moves.position) ; 	
	return list ; 


}








/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/



List* concatenate_list(List* L1,List* L2 ) {

	if(L1 == NULL || L1->count == 0){
		if(L2 == NULL || L2->count == 0){
			if(L2!=NULL){
				free(L2);
				MEMDEALLOC_DEBUG_LIST++;
			}
			return NULL ;
		}
		else
			return L2 ; 

	}

	else if(L2 == NULL || L2->count == 0){
		if(L1 == NULL || L1->count == 0)
		{
			if(L1!=NULL)
			{
				MEMDEALLOC_DEBUG_LIST++;
				free(L1);
			}
			return NULL ;
		}
		else
			return L1 ; 

	}


	else{
	/*verify that both list have the right data type : */
	
	assert(L1->data_type == L2->data_type);

		List* concat = init_empty_list(L1->data_type); 

		L1->end->next = L2->begin;
		L2->begin->prev = L1->end; 
		concat->begin = L1->begin ; 
		concat->end = L2->end; 
		concat->count = L1->count+L2->count;
		concat->data_type = L1->data_type ;
		free(L1); 
		free(L2);
	        MEMDEALLOC_DEBUG_LIST+=2 ; 	
	        return concat ; 	


	}


}




















/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/







List * generate_all_boards(Node* node,uint16_t width , COLOR color) {
	
 	assert(node->data_type == GAME) ;	
	
	List* list = NULL; 
	Game* game =(Game*) (node->value); 
	for(size_t i = 0 ; i < game->pieces_size ; i ++ ){
		if(game->pieces[i].color == color){
		List* temp = generate_boards(node ,width, i ) ; 
		list = concatenate_list(list, temp ) ;
		}
	
	}
	node->next_level = list ; 
	Node* iterator = NULL; 
	for(iterator = list->begin ; iterator != NULL ; iterator = iterator->next)
		iterator->prev_level =  node ; 
	return list ; 

}




















/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/














































/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

















void print_node(Node* node){
	switch(node->data_type){
		case GAME :
			print_board((Game*) (node->value)) ; 
				
			printf("Iterator position :\nWidth : %i    Depth : %i\n",WIDTH , DEPTH );		
		break;

		case STRING : 
		printf("%s \n" ,(char*) (node->value)); 

		break;







	}



}


















/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
static char EXIT ='e'; 
 uint32_t DEPTH = 0 ;
 uint32_t WIDTH = 0 ;

void browse_tree(Tree* tree){

	assert(tree != NULL) ;
	printf("INITIALIZATION\n");
 	print_board(tree->root->value);	
	Node* iterator = tree->root ; 

	char move = ' ' ; 

	while(move != EXIT ) {
	     scanf("%c",&move); 
	     switch(move){
		case 'z' : 
			if(iterator->prev_level != NULL){
				iterator = (iterator->prev_level) ; 
				DEPTH--;
				WIDTH=0 ; 
			}

			

		break;


		case 's' : 
			if(iterator->next_level != NULL){
				assert((iterator->next_level)->count>0);
				iterator = (iterator->next_level)->begin ; 
				DEPTH++;
				WIDTH=0;
					}
			
		break;


		case 'q' :
			if(iterator->prev != NULL){
			iterator = iterator->prev ;
			WIDTH-- ;
			}	
			

		break;


		case 'd' :
			if(iterator->next != NULL){
			iterator = iterator->next ;
			WIDTH++; 
			}	


			

		break;

		default :
		//	printf("unknown action %c \n " , move); 

		break;
		






	     }
	print_node(iterator);	
	}



}

























/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
static int cc = 0 ; 
void generation(Node* iterator,int D,int W,int countD,int countW,COLOR color){
	if(countD<D){
		
		printf("%i\n",cc++); 
		color = (color == BLACK) ? WHITE : BLACK ; 
		List *list = generate_all_boards(iterator,W,color) ;
		Node* it = list->begin ;
		while(it != NULL ){
		

			generation(it , D , W , countD+1 , countW+1 , color ) ; 

		it = it->next; 
		}


	}


}





Tree* generate_tree(Node *root , uint32_t depth,uint32_t width,COLOR begin){
	Tree* tree = init_tree(root); 
	generation(root , depth , width , 0 , 0 , begin ) ; 
	return tree; 


}









/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/








Node* pop_back(List* list){
	
	if(list->count == 1){
		
		Node* M = list->begin ; 
		MEMDEALLOC_DEBUG_LIST++;
		free(list); 
		return M ; 
	}
	else if (list->count > 1 ){
		Node *M = list->begin ; 
		list->begin = list->begin->next;
		list->begin->prev = NULL ; 
		M->next=NULL ;
		M->prev=NULL ; 
		list->count--;
		return M ; 

	}


}














