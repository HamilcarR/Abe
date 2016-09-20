#ifndef MMANAGER_H_INCLUDED
#define MMANAGER_H_INCLUDED
#include <uchar.h>
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



#define MAX_DEBUG_VAR 14 






  static const uint8_t ALLOC_PIECE = 0;
  static const uint8_t ALLOC_GAME = 1;
  static const uint8_t ALLOC_POSITION = 2;
  static const uint8_t ALLOC_NODE = 3;
  static const uint8_t ALLOC_LIST = 4;
  static const uint8_t ALLOC_PLAYER = 5;
  static const uint8_t ALLOC_TREE = 6;

  static const uint8_t DEALLOC_PIECE = 7 ;
  static const uint8_t DEALLOC_GAME = 8 ;
  static const uint8_t DEALLOC_POSITION = 9 ;
  static const uint8_t DEALLOC_NODE = 10 ;
  static const uint8_t DEALLOC_LIST = 11 ;
  static const uint8_t DEALLOC_PLAYER = 12 ;
  static const uint8_t DEALLOC_TREE = 13 ;





 extern uint_fast32_t MEMALLOC_DEBUG_PIECE ;
 extern uint_fast32_t MEMALLOC_DEBUG_GAME ;
 extern uint_fast32_t MEMALLOC_DEBUG_POSITION ;
 extern uint_fast32_t MEMALLOC_DEBUG_NODE ;
 extern uint_fast32_t MEMALLOC_DEBUG_LIST ;
 extern uint_fast32_t MEMALLOC_DEBUG_PLAYER ;
 extern uint_fast32_t MEMALLOC_DEBUG_TREE ;


 extern uint_fast32_t MEMDEALLOC_DEBUG_PIECE ;
 extern uint_fast32_t MEMDEALLOC_DEBUG_GAME ;
 extern uint_fast32_t MEMDEALLOC_DEBUG_POSITION ;
 extern uint_fast32_t MEMDEALLOC_DEBUG_NODE ;
 extern uint_fast32_t MEMDEALLOC_DEBUG_LIST ;
 extern uint_fast32_t MEMDEALLOC_DEBUG_PLAYER ;
 extern uint_fast32_t MEMDEALLOC_DEBUG_TREE ;


extern const char* string_debugs[];

extern void check_memleak();


#endif



