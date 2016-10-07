#include "../headers/Engine.h"
#include <pthread.h>



/********************-- VARS DEFINE --*********************************/



static Node* DEBUG_NODE = NULL ;



























/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/



Node * init_node(void* data, Node* next, Node* prev,List* next_lvl,Node* prev_lvl,N_DATA type){
	Node *node = calloc(1,sizeof(Node));
	mem_debug_increment(ALLOC_NODE); 
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
		
		case NODE :
		free_node(node->value);
		node->value = NULL ; 	
		default :
		node->value = NULL ; 

		break; 

		}


	mem_debug_increment(DEALLOC_NODE); 	
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
mem_debug_increment(DEALLOC_LIST) ; 
free(list) ; 

}











/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/


static size_t DEBUG_COUNTER = 0 ; 

static void free_tree_nodes(Node* root){ 

	

	//TODO : multi threading free.
	if(root->next_level != NULL && root->next_level->begin != NULL){
		Node* iterator = root->next_level->begin ; 
			
		

		while(iterator!=NULL){
			Node *temp = iterator ;	
			iterator=iterator->next;
			free_tree_nodes(temp);
			
		
		}
		mem_debug_increment(DEALLOC_LIST); 
		free(root->next_level) ; 


	
	}
	else if (root->next_level != NULL && root->next_level->begin == NULL){
		free(root->next_level); 
		mem_debug_increment(DEALLOC_LIST);

	}

	
	free_node(root);


}

void free_tree(Tree* tree){
	DEBUG_COUNTER = 0 ;
        
	free_tree_nodes(tree->root) ;
	mem_debug_increment(DEALLOC_TREE);
	free(tree);



}


Tree* init_tree(Node* root){
	Tree* tree = calloc(1,sizeof(Tree));
	mem_debug_increment(ALLOC_TREE);
         	
	tree->root = root; 

	return tree ; 


}
















/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

List* init_list(Node* begin){

	

List* list ; 
list = malloc(sizeof(List)) ;
mem_debug_increment(ALLOC_LIST);
list->count = 1 ; 
list->data_type=begin->data_type;
list->begin = begin ; 
list->end = begin ; 
return list ; 

}







/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/





void add_node_to_list(List* list , Node* node )  {
	assert(list!=NULL);
	if(list->add_mode == FULL_LINKED){
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

	else if (list->add_mode == DOUBLE_LINKED_ONE_LVL) {
			if(list->count == 0 ){
				list->begin = node ; 
				list->end = node ;
				list->count++ ; 
				return ;
			}
			node->prev_level = NULL ; 
			node->next_level = NULL ; 		
		 	node->prev = list->end ; 
		  	(list->end)->next = node;
	  	  	list->end = node ; 	  
		  	node->next = NULL ;
		  	list->count++;
	}
	else if (list->add_mode == ONE_LINK_ONE_LVL_NEXT){
			if(list->count == 0 ){
				list->begin = node ; 
				list->end = node ;
				list->count++ ; 
				return ;
			}
			node->prev_level = NULL ; 
			node->next_level = NULL ; 		
		 	node->prev = NULL; 
		  	(list->end)->next = node;
	  	  	list->end = node ; 	  
		  	node->next = NULL ;
		  	list->count++;




	}




	}
		















/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/





void print_list(List *list){

	assert(list!=NULL);
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

	else if (list->data_type == PTR_ON_NODE){
		Node* it ;
		for(it = list->begin ; it!= NULL ; it=it->next)
		{
			printf("sdsdds\n");
			print_node(  *  ((Node**)(it->value))   );

		}


	}
	



	printf("\n List size is : %i\n",list->count);



}





void display_list(List* list){
	assert(list!=NULL);
	Node* it = list->begin ; 
	while(it!=NULL)
	{	
		print_node(it);
		it=it->next;


	}
	printf("List size is :%i\n" ,list->count);

}











/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/


List* init_empty_list(N_DATA data,ADD_MODE add){
	List* liste = calloc( 1 , sizeof(List));
	mem_debug_increment(ALLOC_LIST) ; 
	liste->count = 0 ; 
	liste->add_mode = add;
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


/*generate all combinations of moves for pieceID and return them as a linked list */
List* generate_boards(Node* game,uint16_t width , size_t pieceID){
	assert(game->data_type == GAME);
	List* list ; 
	list = init_empty_list(GAME,FULL_LINKED) ; 	
	
	Game * data =(Game*) game->value ;

	Piece* p = &(data->pieces[pieceID]);
	Piece** pp = &p ; 
	Moves moves = generate_moves(data, pp);
	int siz = (moves.number<=width) ? moves.number : width; 
		for(int i = 0 ; i < siz ; i ++ ){
			assert(check_valid_position(moves.position[i]) == true) ; 
			Node* P = new_piece_location(moves.position[i] , game , pieceID);
			Game *g1 = data;
			Game *g2 = (Game*)(P->value);
			if(!equal_game(g1,g2))
				add_node_to_list(list , P ) ;
			else
				free_node(P); 	
		

		
	}
	mem_debug_increment(DEALLOC_POSITION);
        free(moves.position) ; 	
	return list ; 


}








/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/



List* concatenate_list(List* L1,List* L2,uint16_t width ) {

	if(L1 == NULL || L1->count == 0){
		if(L2 == NULL || L2->count == 0){
			if(L2!=NULL){
				free(L2);
				mem_debug_increment(DEALLOC_LIST);
			}
			return NULL ;
		}
		else{
			if(L1 != NULL)
			{
				free(L1);                                                      /*forgot these...*/
				mem_debug_increment(DEALLOC_LIST);


			}
			return L2 ; 

		}
	}

	else if(L2 == NULL || L2->count == 0){
		if(L1 == NULL || L1->count == 0)
		{
			if(L1!=NULL)
			{
				mem_debug_increment(DEALLOC_LIST);
				free(L1);
			}
			return NULL ;
		}
		else{
			if(L2!=NULL){
				free(L2);
				mem_debug_increment(DEALLOC_LIST);

			}
			return L1 ; 
		}

	}


	else{
	/*check that both list have the right data type : */
	
	assert(L1->data_type == L2->data_type);

		List* concat = init_empty_list(L1->data_type,FULL_LINKED); 

		L1->end->next = L2->begin;
		L2->begin->prev = L1->end; 
		concat->begin = L1->begin ; 
		concat->end = L2->end; 
		concat->count = L1->count+L2->count;
		concat->data_type = L1->data_type ;
		free(L1); 
		free(L2);
	        mem_debug_increment(DEALLOC_LIST); 
		mem_debug_increment(DEALLOC_LIST); 
		if(concat->count > width){

			Node* iterator = concat->end ; 
			int count = concat->count ; 

			while(count != width)
			{
			assert(iterator != NULL);
			
			Node* temp = iterator ; 

			iterator = iterator->prev;
			free_node(temp);
			count--;
			concat->count--; 

			}
			concat->end = iterator; 
			concat->end->next = NULL ; 	

		}	
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
		list = concatenate_list(list,temp,width ) ;
		}
	
	}
	if(list != NULL) {
	node->next_level = list ; 
	Node* iterator = NULL; 
	for(iterator = list->begin ; iterator != NULL ; iterator = iterator->next){
				
		iterator->prev_level =  node ; 
		((Game*)(iterator->value))->turn = color ;			


		
	}
	return list ; 
	}
	else
		return NULL ; 
		

}




















/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/














































/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

















void print_node(Node* node){
	switch(node->data_type){
		case GAME :
			printf("Iterator position :\nWidth : %i    Depth : %i\n",WIDTH , DEPTH );		
			
			print_board((Game*) (node->value)) ; 
			printf("Iterator color : %s\n", (((Game*) (node->value))->turn ) == BLACK ? "BLACK" : "WHITE" ) ; 
				
		break;

		case STRING : 
		printf("%s \n" ,(char*) (node->value)); 

		break;
		
		case FLOAT :
	       			
			printf("%f \n" ,*((float*) (node->value)));
		break; 


		case INT : 

			printf("%i \n" ,* (int*)(node->value));
		break; 

		case LONG : 
			
			printf("%li \n" , *(long*)(node->value));
		break ; 
		
		case CHAR :

			printf("%c \n" , *(char*)(node->value));
		break ; 
		

		case NODE :
		;
		
			print_node((Node*)(node->value));

		break;



		case PTR_ON_NODE :
		;
		Node ** ptr = node->value ; 
		Node * P = *ptr;
			print_node(P);

		break;
			
			



	}



}


















/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
static char EXIT ='e'; 
 uint32_t DEPTH = 0 ;
 uint32_t WIDTH = 0 ;

void browse_tree(Tree** tree){

	assert(*tree != NULL) ;
	printf("INITIALIZATION\n");
 	print_board((*(tree))->root->value);	
	Node* iterator = (*(tree))->root ; 

	char move = ' ' ; 
	

	void* (*fct_ptr)(void*) =(void*) &free_tree;
	while(move != EXIT ) {
	     scanf("%c",&move); 
	     switch(move){
		case 'z' : 
			if(iterator->prev_level != NULL){
				iterator = (iterator->prev_level) ; 
				DEPTH--;
				WIDTH=0 ; 
			}

			

		print_node(iterator);
		break;


		case 's' : 
			if(iterator->next_level != NULL){
				assert((iterator->next_level)->count>0);
				iterator = (iterator->next_level)->begin ; 
				DEPTH++;
				WIDTH=0;
					}
				
		print_node(iterator);
		break;


		case 'q' :
			if(iterator->prev != NULL){
			iterator = iterator->prev ;
			WIDTH-- ;
			}	
			
		print_node(iterator);

		break;


		case 'd' :
			if(iterator->next != NULL){
			iterator = iterator->next ;
			WIDTH++; 
			}	


		print_node(iterator);
			

		break;
		
		case 'g' :
	       	;	//to get rid of the stupid "a label can only be part of a statement" error
			Game* game = get_board_copy((Game*)iterator->value); 
			COLOR color = game->turn ;


			pthread_create(&f_thread , NULL ,(void*)fct_ptr,(void*)*tree);  	
		//	free_tree(*tree); 
			 
			int depth = 4 , width = 250 ; 
			//TODO : generate tree using threads			
			Node* N = init_node(game,NULL,NULL,NULL,NULL,GAME); 
			*tree = generate_tree(N , depth , width , color ) ;  
			iterator =(*tree)->root ; 
			
			
			print_node(iterator);

		
		break ; 

		
		case 'b' :
		;
			const char* ca = is_leaf_tree(*tree , iterator) ? "yes" : "no";
			
			printf(" Is leaf : %s \n " ,ca) ;  
			if (ca == "yes"){
				printf("PREVIOUS :  \n" );
				print_node(DEBUG_NODE->prev_level);
			
			}



		break; 

		default :
		//	printf("unknown action %c \n " , move); 

		break;
		






	     }

	
	pthread_join(f_thread , NULL) ; 

	}



}

























/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
static int cc = 0 ; 
void generation(Node* iterator,uint8_t D,uint8_t W,uint8_t countD,uint8_t countW,COLOR color){
	if(countD<D){
		

		 	
		COLOR temp =  (color == BLACK) ? WHITE : BLACK ;  
		List *list = generate_all_boards(iterator,W,temp);
		if(list!=NULL){
		Node* it = list->begin ;
		while(it != NULL ){
				
			
			
			generation(it , D , W , countD+1 , countW+1 , temp ) ; 

		it = it->next; 
		}
	}

}


}





Tree* generate_tree(Node *root , uint8_t depth,uint8_t width,COLOR begin){
	Tree* tree = init_tree(root);
	
	generation(root , depth , width , 0 , 0 , begin ) ; 
	return tree; 


}









/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/








Node* pop_back(List* list){
	
	if(list->count == 1){
		
		Node* M = list->begin ; 
		mem_debug_increment(DEALLOC_LIST);
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





/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/


bool is_leaf_list(List* list, Node* node){
//	assert(list->data_type == node->data_type && node->data_type == GAME);
	Node* it = list->begin ; 
	while(it != NULL){
		Game *g1 = node->value;
		Game *g2 = it->value ; 
		if(equal_game(g1,g2) == true )
			return true;
	
		it=it->next; 
	}
	return false;



}

static bool search_node(Node* iterator , Game* comparator ){

	bool a = false;
	if(iterator->next_level == NULL && equal_game(comparator ,(Game*) iterator->value)){
		DEBUG_NODE = iterator ; 
		return true ; 

	}


	else if(iterator->next_level != NULL && iterator->next_level->count!=0 ){
		Node* it = iterator->next_level->begin ; 

		while(it!=NULL){
			
		       a = a|| search_node(it , comparator) ;
			it=it->next; 
		}

	return a ; 
	}
	else
		return false; 


}

bool is_leaf_tree(Tree* T , Node* node){
	Node* root = T->root ; 
	assert(node->data_type == GAME) ;
	return search_node(root ,(Game*) node->value);



}


static void seek_leafs(Node* node, List* list){
	if(node->next_level==NULL || node->next_level->count == 0){
		
		Node *N = init_node((void*) node,NULL,NULL,NULL,NULL,NODE);
		add_node_to_list(list,N);


	}
	else{
		Node* iterator = node->next_level->begin;
		while(iterator!=NULL){
		seek_leafs(iterator,list);
		iterator=iterator->next;
		}

	}
	

}



List* get_leafs(Tree* tree){

	List* list = init_empty_list(NODE,ONE_LINK_ONE_LVL_NEXT); 
	
	seek_leafs(tree->root,list);
	return list ; 

}




	



/***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/



