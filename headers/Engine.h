#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "Config.h"
#include "Move.h"
#include <pthread.h>



extern uint32_t DEPTH  ;  //Depth of search tree 
extern uint32_t WIDTH  ;  //Width of search tree


/* Determines how the linked list can be iterated. 
 *
 * FULL_LINKED = every pointers are used:
 * 			-prev
 * 			-next
 * 			-next_level
 * 			-prev_level
 *
 * DOUBLE_LINKED_ONE_LVL = only two pointers used:
 * 			-next
 * 			-prev
 *
 * ONE_LINK_ONE_LVL_NEXT = only one pointer used :
 * 			-next 
 *
 *
 *
 *
 */
enum ADD_MODE {FULL_LINKED = 1 , DOUBLE_LINKED_ONE_LVL = 1 , ONE_LINK_ONE_LVL_NEXT = 2 };
typedef enum ADD_MODE ADD_MODE ; 



/*Node data...trying to use some generic data:
 *
 * GAME for an instance of a game
 * ALLOC_PTR for an allocation
 * STRING for char* 
 * NODE for a Nodeception
 * etc..
 */
 enum N_DATA {GAME = 0 , ALLOC_PTR = 1 ,STRING = 3 , FLOAT = 2 , INT = 4 , LONG = 5 , CHAR = 6, NODE = 7,PTR_ON_NODE= 8,PTR = 	9};
typedef enum N_DATA N_DATA ; 

struct Node ;
struct List ;
struct Tree ;
struct Array ; 


typedef struct Node Node;
 struct Node{
	 
    void* value;
    int min_max ;   
    N_DATA data_type;  
    Node *prev ;
    Node *next ;/* pointer to nodes of the same level */
    struct Node *prev_level; /*pointer to up level nodes*/
    struct List *next_level ;
     
};




typedef struct List List; 
struct List {
    int count ;
    Node* begin ;
    Node* end   ;
    N_DATA data_type ;
    ADD_MODE add_mode; 

};
typedef struct Tree Tree;
 struct Tree{
    Node *root;
};

typedef struct Array Array ; 

 struct Array{

	enum N_DATA data_type ; 
	void** array ;
	size_t array_size ;
	
};




/*free ressources...*/
 void free_tree(Tree* tree);
 void free_node(Node* node);
 void free_list(List* list);
 void free_array(Array *array);
/********************/



/*Init ressources...*/

Tree * init_tree(Node* root); // initialize the search tree
/**
 * @File Engine.h
 * @Brief  
 *
 * @Param data
 * @Param next
 * @Param previous
 * @Param next_level
 * @Param prev_level
 *
 * @Returns  Node* 
 */
Node * init_node(void* data,Node* next,Node* previous,List * next_level ,Node * prev_level,N_DATA type) ;



/**
 * @Brief  initialize a list
 *
 * @Param begin
 * @Param end
 *
 * @Returns  List*
 */
List* init_list(Node* begin);


/**
 * \file Engine.h
 * \Brief  initialize an empty list with a certain data type
 *
 * \Param data
 *
 * \Returns  List*
 */
List* init_empty_list(N_DATA data,ADD_MODE add);






/**
 * @Brief  
 *
 * @Param data
 *
 * @Returns  
 */
Array* init_array(N_DATA data);






/********************/





void add_node_to_list(List* list , Node* node) ; 
void delete_node(List* list , Node* node);

char* toString(List *list); 

/**
 * \file Engine.h
 * \Brief print the content of the list in terminal 
 *
 * \Param list 
 */
void print_list(List* list);


void display_list(List* list);



/**
 * \File Engine.h
 * \Brief Given a certain board configuration and a piece,returns all moves possible in the form of multiple boards,in a list
 *
 * \Param game The board to generate the next moves from 
 * \Param piece The id of the piece in the array ,we want to move
 *
 * \Returns  List*
 */
List* generate_boards(Node *root ,uint16_t width,  size_t id) ;


/**
 * \Brief  
 *
 * \Param 
 * \Param List
 *
 *  
 */
List* concatenate_list(List* , List* , uint16_t) ;









List* generate_all_boards(Node*,uint16_t width , COLOR color);









/**
 * \Brief  A function to travel across the tree... use 'z' to go up the hierarchy,
 * 'q' to go left , 'd' to go right,and 's' to go down.Use 'g' to generate a new tree from 
 * the current iterator position.
 *
 * \Param tree
 */
void browse_tree(Tree** tree);







/**
 * \Brief  generate all combinations according to the parameters
 *
 * \Param root
 * \Param depth
 * \Param width
 * \Param datatype
 *
 * \Returns  
 */
Tree* generate_tree(Node* root , uint8_t depth , uint8_t width,COLOR color); 
/*easy overflow here...
 * 		space taken on RAM = 0(width^depth) 
 *			
 *
 *
 *generate tree by step,on iterator position ? / 
 *
 *
 *
 *
 * */



/**
 * \Brief  Free previous tree structure,then generate the next nodes and store them back to tree pointer
 *
 * \Param tree
 * \Param depth
 * \Param width
 */
void clean_and_generate_tree(Tree** tree , uint8_t depth , uint8_t width) ;



/**
 * \Brief  printing the value of a node
 *
 * \Param node
 */
void print_node(Node* node);




Node* pop_back(List*);

bool is_leaf_list(List* T , Node* N );
bool is_leaf_tree(Tree* T , Node* N );






List* get_leafs(Tree* tree);



























#endif // ENGINE_H_INCLUDED
