#include "../headers/mmanager.h"



 





 const char* string_debugs[] = {
"Allocation for struct PIECE",
"Allocation for struct GAME",
"Allocation for struct POSITION",
"Allocation for struct NODE",
"Allocation for struct LIST",
"Allocation for struct PLAYER",
"Allocation for struct TREE",

"Deallocation for struct PIECE",
"Deallocation for struct GAME",
"Deallocation for struct POSITION",
"Deallocation for struct NODE",
"Deallocation for struct LIST",
"Deallocation for struct PLAYER",
"Deallocation for struct TREE"

};

  uint_fast32_t MEMALLOC_DEBUG_PIECE  = 0 ;
  uint_fast32_t MEMALLOC_DEBUG_GAME  = 0 ;
  uint_fast32_t MEMALLOC_DEBUG_POSITION  = 0 ;
  uint_fast32_t MEMALLOC_DEBUG_NODE  = 0 ;
  uint_fast32_t MEMALLOC_DEBUG_LIST  = 0 ;
  uint_fast32_t MEMALLOC_DEBUG_PLAYER  = 0 ;
  uint_fast32_t MEMALLOC_DEBUG_TREE  = 0 ;

  uint_fast32_t MEMDEALLOC_DEBUG_PIECE = 0 ;
  uint_fast32_t MEMDEALLOC_DEBUG_GAME = 0 ;
  uint_fast32_t MEMDEALLOC_DEBUG_POSITION = 0 ;
  uint_fast32_t MEMDEALLOC_DEBUG_NODE = 0 ;
  uint_fast32_t MEMDEALLOC_DEBUG_LIST = 0 ;
  uint_fast32_t MEMDEALLOC_DEBUG_PLAYER = 0 ;
  uint_fast32_t MEMDEALLOC_DEBUG_TREE = 0 ;



 

  /**********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/





 void check_memleak(){
  uint_fast32_t array[MAX_DEBUG_VAR]={
  MEMALLOC_DEBUG_PIECE ,
  MEMALLOC_DEBUG_GAME ,
  MEMALLOC_DEBUG_POSITION ,
  MEMALLOC_DEBUG_NODE ,
  MEMALLOC_DEBUG_LIST ,
  MEMALLOC_DEBUG_PLAYER ,
  MEMALLOC_DEBUG_TREE ,
  MEMDEALLOC_DEBUG_PIECE ,
  MEMDEALLOC_DEBUG_GAME ,
  MEMDEALLOC_DEBUG_POSITION ,
  MEMDEALLOC_DEBUG_NODE ,
  MEMDEALLOC_DEBUG_LIST ,
  MEMDEALLOC_DEBUG_PLAYER ,
  MEMDEALLOC_DEBUG_TREE 	
  };	


	for(int i = 0 ; i < MAX_DEBUG_VAR/2 ; i++)
		printf("%s:%i     %s:%i \n",string_debugs[i],(int)array[i],string_debugs[i+MAX_DEBUG_VAR/2],(int)array[i+MAX_DEBUG_VAR/2]); 		


	

	

 }
