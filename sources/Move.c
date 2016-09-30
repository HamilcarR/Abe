#include "../headers/Move.h"














/*******************************************************************************************************************************************************************************************************/

/*return a pointer on the piece located at pos*/
 Piece* select_piece(Game* game,Position pos){
     Piece* P = NULL ;
    for(size_t i = 0 ; i < game->pieces_size ; i++){
        if((game->pieces[i]).position.x == pos.x && (game->pieces[i]).position.y == pos.y)
           {
               P =  &(game->pieces[i]) ;

               return P ;

           }

    }
    return NULL;
	
	
}

/*******************************************************************************************************************************************************************************************************/
/*check if a friend is at position pos and has color*/
static bool check_friend(COLOR color, Game* game, Position pos){
    for(size_t i = 0 ; i < game-> pieces_size ; i++ ) {
			Piece* p = &game->pieces[i] ;
			if(p->color== color && p->position.x == pos.x && p->position.y == pos.y){
				return true;
			}

	}
	return false;




}



/*******************************************************************************************************************************************************************************************************/
/*Check if an ennemy is at position pos and has !color*/
static bool check_enemy(COLOR color, Game * game,Position pos) {
		for(size_t i = 0 ; i < game-> pieces_size ; i++ ) {
			Piece* p = &game->pieces[i] ;
			if(p->color!= color && p->position.x == pos.x && p->position.y == pos.y){
				return true;
			}

	}
	return false;


}

/*******************************************************************************************************************************************************************************************************/
/*if there's already a certain move in array */
static bool present_move(Moves move,Position pos){
    for(int i = 0 ; i < move.number ; i++){
        if(move.position[i].x == pos.x && move.position[i].y == pos.y)
            return true;

    }
    return false;

}





/********************************************************************************************************************************************************************************************************/

static bool present_piece(Game* game, Position pos ) {

	return (check_enemy(WHITE , game , pos) || check_friend(WHITE , game , pos) ) ; 


}














/*******************************************************************************************************************************************************************************************************/


   bool equal_pieces(Piece* piece1, Piece* piece2){

         if(piece1->color != piece2->color || piece1->type != piece2->type || (piece1->position.x != piece2->position.x || piece1->position.y != piece2->position.y))
            return false ;
        else
            return true;



   }




/*******************************************************************************************************************************************************************************************************/
    static void move(Piece* p , Position pos){

        p->position.x=pos.x;
        p->position.y=pos.y;

    }


/*******************************************************************************************************************************************************************************************************/

    void kill(Piece** piece, Game * game , int k){
        Piece *target=&(game->pieces[k]);
        Piece *pieces = calloc(game->pieces_size - 1 ,sizeof(Piece));
	MEMALLOC_DEBUG_PIECE++;
        uint8_t id = get_pieceID(*target);
        game->stack[id]++;
        int x =target->position.x;
        int y =target->position.y;
        (*piece)->position.x=x ;
        (*piece)->position.y=y ;

       uint8_t j = 0 ;
        for(uint8_t i = 0 ; i < game->pieces_size ; i++){
             bool a = equal_pieces(&(game->pieces[i]),target) ;
             if(!a){
                pieces[j] = game->pieces[i];
                j++;
             }


        }


        game->pieces_size --;
	Piece* temp_p = game->pieces;
	game->pieces = pieces;
       
       
	(*piece) = select_piece(game,(*piece)->position);
	free(temp_p); 
	MEMDEALLOC_DEBUG_PIECE++;

    }





    /*****************************************************************************************************************************************************************************************************/
  



Moves generate_moves(Game* game, Piece** piece){

    Moves temp ;
        switch((*piece)->type){
            case PAWN :
                temp = move_pawn(game,(*piece));
            break;

            case BISHOP :
                temp = move_bishop(game,(*piece));
            break;


            case QUEEN :

                temp = move_queen(game,(*piece));
            break;


            case KNIGHT :

                temp = move_knight(game,(*piece));

            break;


            case KING :

                temp = move_king(game,(*piece));


            break;


            case ROOK :

                temp = move_rook(game,(*piece));
            break;


    }

return temp ; 


}






static  ERROR move_temp(Game * game , Piece** piece , Position pos){

    if((pos.x != (*piece)->position.x || pos.y != (*piece)->position.y) && check_valid_position(pos)){
   Moves temp = generate_moves(game,piece) ; 
    for(uint8_t i = 0 ; i< temp.number ; i++){
        if(temp.position[i].x == pos.x && temp.position[i].y == pos.y){
            for(uint8_t j = 0 ; j < game->pieces_size ; j++){

                if(game->pieces[j].position.x == pos.x && game->pieces[j].position.y == pos.y )
                    {
                            if(((*piece)->color == BLACK && game->pieces[j] .color == WHITE) || ((*piece)->color == WHITE && game->pieces[j] .color == BLACK)){

                                kill(piece,game,j);
				MEMDEALLOC_DEBUG_POSITION++;
                                free(temp.position);
                                return OKAY;

                            }
                            else if (((*piece)->color == BLACK && game ->pieces[j].color == BLACK) || ((*piece)->color == WHITE && game ->pieces[j].color == WHITE)){
                               
				MEMDEALLOC_DEBUG_POSITION++;	
                                free(temp.position);
				    return NOT_ENEMY;


                            }
		    }
            }




             move((*piece),pos);
	  //  piece = select_piece(game,piece->position);
	     MEMDEALLOC_DEBUG_POSITION++;
   	     free(temp.position);
             return OKAY;


        }

    }
    MEMDEALLOC_DEBUG_POSITION++; 
    free(temp.position);
    return WRONG_MOVE;
    }
    else{

        return WRONG_MOVE;

    }


    }

    /*******************************************************************************************************************************************************************************************************/

    Moves move_pawn(Game *game,Piece *piece){
	Moves moves;
	moves.number = 0 ;
	moves.position = calloc(moves.number , sizeof(Position)); //TODO : free
	MEMALLOC_DEBUG_POSITION++;
        if(piece->color == WHITE){
		Position enem_position ;
		enem_position.x = piece->position.x-1;
		enem_position.y = piece->position.y-1;
		if(check_valid_position(enem_position) && check_enemy(WHITE,game,enem_position)){

		Position * ptr_free = moves.position ;
		if((ptr_free =realloc(moves.position , (moves.number+1)* sizeof(Position)))!=NULL){
          	        moves.number++;
			moves.position = ptr_free;
			moves.position[moves.number-1].x = enem_position.x ;
			moves.position[moves.number-1].y = enem_position.y ;
		}
		else
		{
		free(moves.position);
		MEMDEALLOC_DEBUG_POSITION++;
		printf("\n move_pawn problem realloc 1\n" ) ;
		Moves m ;
		m.number= 0 ;
		return m ;
		}
		}

		enem_position.y = piece->position.y+1;
		if(check_valid_position(enem_position) && check_enemy(WHITE,game,enem_position)){

		Position* ptr_free = moves.position ;
		if((ptr_free =realloc(moves.position, (moves.number+1) * sizeof(Position)))!=NULL){
			moves.position = ptr_free;
			moves.number++;
			moves.position[moves.number-1].x = enem_position.x ;
			moves.position[moves.number-1].y = enem_position.y ;
		}
		else
		{
		MEMDEALLOC_DEBUG_POSITION++;
		free(moves.position);
		printf("\n move_pawn problem realloc 2\n" ) ;
		Moves m ;
		m.number= 0 ;
		return m;
		}



		}

	    	if(piece->position.x == BOARD_SIZE-2){
		  	    
			Position * ptr_free = moves.position ;
			Position p_pos,f_pos; 
			p_pos.x = BOARD_SIZE-3 ; 
		        p_pos.y = piece->position.y ; 
			f_pos.x = BOARD_SIZE - 4 ; 
			f_pos.y = p_pos.y ;
		        int size1 = (check_enemy(WHITE,game,p_pos) || check_friend(WHITE,game,p_pos)) ? 1 : 0 ; 
			int size2 = (check_enemy(WHITE,game,f_pos) || check_friend(WHITE,game,f_pos)) ? 1 : 0 ; 	
			int sizei = (size1 == 1 ) ? 0 :(  (size2 == 1) ? 1 :  2  ) ;         //yes it's weird...yes I like it that way...no,I don't want to change it .
			

			if(moves.number+sizei>0){
			if((ptr_free =realloc(moves.position , (sizei+moves.number) * sizeof(Position)))!=NULL){
			
			moves.position = ptr_free;
			if(sizei == 2 )
			{

			moves.number++;
			moves.position[moves.number-1].x = piece->position.x - 1 ;
			moves.position[moves.number-1].y = piece->position.y ;
			moves.number++;
			moves.position[moves.number-1].x = piece->position.x - 2 ;
			moves.position[moves.number-1].y = piece->position.y ;

			}
			else if(sizei == 1 && size2 == 1 ){
			moves.number++ ;  
			moves.position[moves.number-1].x = piece->position.x - 1  ;
			moves.position[moves.number-1].y = piece->position.y ; 


			}
			}
			else
			{
			MEMDEALLOC_DEBUG_POSITION++;
			free(moves.position);
			printf("\n move_pawn problem realloc 3\n" ) ;
			Moves m ;
			m.number= 0 ;
			return m;
			}

			}


		}

	      	else {
			Position * ptr_free = moves.position ;
			Position enem ;
		        enem.x = piece->position.x - 1 ;
			enem.y = piece->position.y ;
			int a = (check_enemy(WHITE,game,enem) || check_friend(WHITE,game,enem) ) ? 0 : 1 ;

			Position P1 = {.x = piece->position.x-1 , .y = piece->position.y };
			bool valid_move_1M = check_valid_position(P1); 
			
			if(moves.number+a > 0  && valid_move_1M){

				if((ptr_free =realloc(moves.position ,(moves.number+a) *  sizeof(Position)))!=NULL){
				moves.position = ptr_free;
					if(a != 0 ){
						moves.number++;
						moves.position[moves.number-1].x = piece->position.x - 1 ;
						moves.position[moves.number-1].y = piece->position.y ;
					}
				}
				else
				{
				MEMDEALLOC_DEBUG_POSITION++;
				free(moves.position);
				printf("\n move_pawn problem realloc 4\n" ) ;
				Moves m ;
				m.number= 0 ;
				return m;
				}
			}
	       	}

		return moves;


        }

        else{
		Position enem_position ;
		enem_position.x = piece->position.x+1;
		enem_position.y = piece->position.y+1;
		if(check_valid_position(enem_position) && check_enemy(BLACK,game,enem_position)){

		Position * ptr_free = moves.position ;
		if((ptr_free =realloc(moves.position ,(moves.number+1)*sizeof(Position)))!=NULL){
			moves.position = ptr_free;
			moves.number++;
			moves.position[moves.number-1].x = enem_position.x ;
			moves.position[moves.number-1].y = enem_position.y ;
		}
		else
		{
		MEMDEALLOC_DEBUG_POSITION++;
		free(moves.position);
		printf("\n move_pawn problem realloc 5\n" ) ;
		Moves m ;
		m.number= 0 ;
		return m;
		}
		}

		enem_position.y = piece->position.y-1;
		if(check_valid_position(enem_position) && check_enemy(WHITE,game,enem_position)){

		Position * ptr_free = moves.position ;
		if((ptr_free =realloc(moves.position , (moves.number+1)*sizeof(Position)))!=NULL){
			moves.position = ptr_free;
			moves.number++;
			moves.position[moves.number-1].x = enem_position.x ;
			moves.position[moves.number-1].y = enem_position.y ;
		}
		else
		{
		MEMDEALLOC_DEBUG_POSITION++;
		free(moves.position);
		printf("\n move_pawn problem realloc 6\n" ) ;
		Moves m ;
		m.number= 0 ;
		return m ;
		}




		}

	    	if(piece->position.x == 1){
			Position p_pos,f_pos; 
			p_pos.x = 2 ; 
		        p_pos.y = piece->position.y ; 
			f_pos.x = 3 ; 
			f_pos.y = p_pos.y ;
		        int size1 = (check_enemy(BLACK,game,p_pos) || check_friend(BLACK,game,p_pos)) ? 1 : 0 ; 
			int size2 = (check_enemy(BLACK,game,f_pos) || check_friend(BLACK,game,f_pos)) ? 1 : 0 ; 	
			

			int sizei = (size1 == 1 ) ? 0 :(  (size2 == 1) ? 1 :  2  ) ;         //yes it's weird...yes I like it that way...no,I don't want to change it .
		
			Position * ptr_free = moves.position ;
			if(moves.number+sizei > 0 ){
				if((ptr_free =realloc(moves.position , (moves.number+sizei)*sizeof(Position)))!=NULL){
					moves.position = ptr_free;
					if(sizei == 2 )
					{
					moves.number++;
					moves.position[moves.number-1].x = piece->position.x + 1 ;
					moves.position[moves.number-1].y = piece->position.y ;
					moves.number++;
					moves.position[moves.number-1].x = piece->position.x + 2 ;
					moves.position[moves.number-1].y = piece->position.y ;

					}
					else if(sizei == 1 && size2 == 1 ){
					moves.number++ ;  
					moves.position[moves.number-1].x = piece->position.x + 1  ;
					moves.position[moves.number-1].y = piece->position.y ; 


					}
				}	
				else
				{
				MEMDEALLOC_DEBUG_POSITION++;
				free(moves.position);
				printf("\n move_pawn problem realloc 7\n" ) ;
				Moves m ;
				m.number= 0 ;
		       		return m;
				}
			}


		}

	      	else {
			Position enem ;
		        enem.x = piece->position.x + 1 ;
			enem.y = piece->position.y ;
			int a = (check_enemy(BLACK,game,enem) || check_friend(BLACK,game,enem) ) ? 0 : 1 ; 
			Position* ptr_free = moves.position ;
			Position P1 = {.x = piece->position.x+1 , .y = piece->position.y };
			bool valid_move_1M = check_valid_position(P1); 
			
			if(moves.number+a > 0 && valid_move_1M) {
				if((ptr_free =realloc(moves.position ,(moves.number+a) *  sizeof(Position)))!=NULL){
					moves.position = ptr_free;
						if(a != 0 ){
							moves.number++;
							moves.position[moves.number-1].x = piece->position.x + 1 ;
							moves.position[moves.number-1].y = piece->position.y ;
						}
				}	
				else
				{
				MEMDEALLOC_DEBUG_POSITION++;
				free(moves.position);
				printf("\n move_pawn problem realloc 8\n" ) ;
				Moves m ;
				m.number= 0 ;
				return m;
				}
			}
			
	       	}

		return moves;


	}


    }

    /*******************************************************************************************************************************************************************************************************/

    Moves move_king(Game *game,Piece *piece){
	Moves moves;
	moves.number = 0 ;
	moves.position = calloc(moves.number , sizeof(Position));	
	MEMALLOC_DEBUG_POSITION++;
    	Position var = piece->position;
	Position up ;
        Position down ;
	Position left;
	Position right;
	Position up_right;
	Position up_left;
	Position down_left;
	Position down_right;

	up.x = var.x ;
	up.y = var.y + 1 ;

       	down.x = var.x ;
	down.y = var.y - 1 ;

	left.x = var.x - 1 ;
	left.y = var.y ;

	right.x = var.x + 1 ;
	right.y = var.y ;

	up_right.x = var.x + 1 ;
	up_right.y = var.y + 1 ;

	up_left.x = var.x - 1 ;
	up_left.y = var.y + 1 ;

	down_left.x = var.x - 1 ;
	down_left.y = var.y - 1 ;

	down_right.x = var.x + 1 ;
	down_right.y = var.y - 1 ;


	 Position position[8] = {up,down,left,right,up_right,up_left,down_left,down_right};

	for(int i = 0 ; i < 8 ; i++){
		if(check_valid_position(position[i] ) && !check_friend(piece->color,game,position[i])) {
		  Position *ptr_free;
	  	  if((ptr_free=realloc(moves.position,(moves.number+1)*sizeof(Position)))!=NULL){
			moves.position = ptr_free;
			moves.number++;
			moves.position[moves.number-1] = position[i] ;
		  }
		   else{
			MEMDEALLOC_DEBUG_POSITION++;
			printf("realloc failed , move_king()") ;
			free(moves.position) ;
			break ; 
		   }

		}


	}



	return moves;
	//TODO : little rook






    }

    /*******************************************************************************************************************************************************************************************************/

    Moves move_queen(Game *game,Piece *piece){
	Moves moves ;
	moves.number = 0 ;
	moves.position = calloc(moves.number,sizeof(Position));
	MEMALLOC_DEBUG_POSITION++;
	/*the queen has bishops's and rooks's moves*/
         Moves m1 = move_bishop(game,piece); 
        Position * ptr_free;
	if(m1.number != 0 ){
        ptr_free = realloc(moves.position , (m1.number+moves.number) * sizeof(Position));
        if(ptr_free == NULL){
            printf("ERROR REALLOC Move queen");
            free(moves.position);    
	    MEMDEALLOC_DEBUG_POSITION++;
        }
        else{
            moves.position = ptr_free;

            for(int i = 0 ; i < m1.number ; i ++ )
                moves.position[i+moves.number] = m1.position[i];

             moves.number += m1.number;

        }
	}


        ptr_free = NULL;


	     Moves m = move_rook(game,piece);
	if(m.number != 0 ) {
        ptr_free = realloc(moves.position , (m.number+moves.number) * sizeof(Position));
        if(ptr_free == NULL){
            printf("ERROR REALLOC 2");
	    MEMDEALLOC_DEBUG_POSITION++; 
            free(moves.position);

        }
        else{
            moves.position = ptr_free;

            for(int i = 0 ; i < m.number ; i ++ )
                moves.position[i+moves.number] = m.position[i];

             moves.number += m.number;

        }



	}
			
	
		free(m1.position);	
		free(m.position);
		MEMDEALLOC_DEBUG_POSITION+=2;


		return moves;
    }

    /*******************************************************************************************************************************************************************************************************/

    Moves move_knight(Game *game,Piece *piece){
          Moves moves;
        moves.number = 0 ;
        moves.position = calloc(moves.number , sizeof(Position));
	MEMALLOC_DEBUG_POSITION++;
	Position origin = piece->position; 
	Position dest1;
	Position dest2;
	Position dest3;
	Position dest4;
	Position dest5;
	Position dest6;
	Position dest7;
	Position dest8;

	dest1.x = origin.x-1; 
	dest1.y = origin.y-2; 

	dest2.x = origin.x-2;
	dest2.y = origin.y-1;

	dest3.x = origin.x-2;
	dest3.y = origin.y+1;

	dest4.x = origin.x-1;
	dest4.y = origin.y+2; 

	dest5.x = origin.x+1;
	dest5.y = origin.y+2; 

	dest6.x = origin.x+2;
	dest6.y = origin.y+1; 
	
	dest7.x = origin.x+2;
	dest7.y = origin.y-1; 
	
	dest8.x = origin.x+1;
	dest8.y = origin.y-2; 
	
	Position dest[8] = {dest1,dest2,dest3,dest4,dest5,dest6,dest7,dest8};
		
	for(int i = 0 ; i < 8 ; i++){
		

		if(check_valid_position(dest[i]) && !check_friend(piece->color,game,dest[i])){
			Position *ptr_free ;
			ptr_free = realloc(moves.position,(moves.number+1)*sizeof(Position));
			if(ptr_free != NULL){
				moves.position = ptr_free; 
				moves.number++ ;
				moves.position[moves.number-1] = dest[i];  

			}

			else{
			     printf("REALLOC PROBLEM MOVE KNIGHT") ;

			     MEMDEALLOC_DEBUG_POSITION++;
			     free(moves.position ) ; 

			}
		

		}
	}


	


	return moves; 

    }

    /*******************************************************************************************************************************************************************************************************/

    Moves move_rook(Game *game,Piece *piece){
        Moves moves;
        moves.number = 0 ;
        moves.position = calloc(moves.number , sizeof(Position));

	MEMALLOC_DEBUG_POSITION++;


    /*UP*/


		for(int i = 0 ; piece->position.x - i > 0 ; i++){

		Position pos ;
		pos.x = piece->position.x - i - 1 ;
		pos.y = piece->position.y ;

		bool friend = check_friend(piece->color,game,pos);
		bool enemy = check_enemy(piece->color,game,pos);
		bool valid = check_valid_position(pos); 
		if(!friend && !enemy && valid){
                Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position)))!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;

                }
                else{
                    printf("move rook problem realloc \n");

		    MEMDEALLOC_DEBUG_POSITION++;
                    cfree(moves.position);
                    break;

                }

		}
		else if (enemy && valid) {
                 Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;
                    break;

                }
                else{
                    printf("move rook problem realloc 2 \n");
                    
		    MEMDEALLOC_DEBUG_POSITION++;
		    cfree(moves.position);
                    break;

                }
		}
		else if(friend){
            break;
		}

}



    /*DOWN*/

		for(int i = 0 ; piece->position.x + i < BOARD_SIZE - 1  ; i++){

		Position pos ;
		pos.x = piece->position.x + i + 1 ;
		pos.y = piece->position.y ;

		bool valid = check_valid_position(pos); 
		bool friend = check_friend(piece->color,game,pos);
		bool enemy = check_enemy(piece->color,game,pos);
		if(!friend && !enemy && valid){
                Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;

                }
                else{
		    
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move rook problem realloc \n");
                    cfree(moves.position);
                    break;

                }

		}
		else if (enemy && valid) {
                 Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;
                    break;

                }
                else{

		    MEMDEALLOC_DEBUG_POSITION++;
                    printf("move rook problem realloc 2 \n");
                    cfree(moves.position);
                    break;

                }
		}
		else if(friend){
            break;
		}



	
}


    /*RIGHT*/


	for(int i = 0 ; piece->position.y + i < BOARD_SIZE - 1  ; i++){

		Position pos ;
		pos.x = piece->position.x ;
		pos.y = piece->position.y + i + 1 ;
	
		bool valid = check_valid_position(pos); 
		bool friend = check_friend(piece->color,game,pos);
		bool enemy = check_enemy(piece->color,game,pos);
		if(!friend && !enemy && valid){
                Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move rook problem realloc \n");
                    cfree(moves.position);
                    break;

                }

		}
		else if (enemy && valid) {
                 Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;
                    break;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move rook problem realloc 2 \n");
                    cfree(moves.position);
                    break;

                }
		}
		else if(friend){
            break;
		}



}

    /*LEFT*/

		for(int i = 0 ; piece->position.y - i > 0   ; i++){

		Position pos ;
		pos.x = piece->position.x ;
		pos.y = piece->position.y - i - 1 ;

		bool valid = check_valid_position(pos); 
		bool friend = check_friend(piece->color,game,pos);
		bool enemy = check_enemy(piece->color,game,pos);
		if(!friend && !enemy && valid){
                Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move rook problem realloc \n");
                    cfree(moves.position);
                    break;

                }

		}
		else if (enemy && valid) {
                 Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;
                    break;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move rook problem realloc 2 \n");
                    cfree(moves.position);
                    break;

                }
		}
		else if(friend){
            break;
		}



		}

		return moves;



    }

    /*******************************************************************************************************************************************************************************************************/

    Moves move_bishop(Game *game,Piece *piece){
          Moves moves;
        moves.number = 0 ;
        moves.position = calloc(moves.number , sizeof(Position));

	MEMALLOC_DEBUG_POSITION++;
        /*diagonal down right*/
		for(int i = 0 ; piece->position.x + i < BOARD_SIZE-1 &&
                        piece->position.y + i < BOARD_SIZE-1 ; i++){

		Position pos ;
		pos.x = piece->position.x + i + 1 ;
		pos.y = piece->position.y + i + 1 ;

		bool valid = check_valid_position(pos); 
		bool friend = check_friend(piece->color,game,pos);
		bool enemy = check_enemy(piece->color,game,pos);
		if(!friend && !enemy && valid){
                Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move bishop problem realloc \n");
                    cfree(moves.position);
                    break;

                }

		}
		else if (enemy && valid) {
                 Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;
                    break;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move bishop problem realloc 2 \n");
                    cfree(moves.position);
                    break;

                }
		}
		else if(friend){
            break;

		}



		}


		/*diagonal up right*/
		for(int i = 0 ; piece->position.x - i > 0 &&
                        piece->position.y + i < BOARD_SIZE-1 ; i++){

		Position pos ;
		pos.x = piece->position.x - i - 1 ;
		pos.y = piece->position.y + i + 1 ;

		bool valid = check_valid_position(pos); 
		bool friend = check_friend(piece->color,game,pos);
		bool enemy = check_enemy(piece->color,game,pos);
		if(!friend && !enemy && valid){
                Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move bishop problem realloc \n");
                    cfree(moves.position);
                    break;

                }

		}
		else if (enemy && valid) {
                 Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;
                    break;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move bishop problem realloc 2 \n");
                    cfree(moves.position);
                    break;

                }
		}
		else if(friend){
            break;

		}

		}

		/*diagonal up left*/
		for(int i = 0 ; piece->position.x - i > 0 &&
                        piece->position.y - i >0 ; i++){

		Position pos ;
		pos.x = piece->position.x - i - 1 ;
		pos.y = piece->position.y - i - 1 ;

		bool valid = check_valid_position(pos); 
		bool friend = check_friend(piece->color,game,pos);
		bool enemy = check_enemy(piece->color,game,pos);
		if(!friend && !enemy && valid){
                Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move bishop problem realloc \n");
                    cfree(moves.position);
                    break;

                }

		}
		else if (enemy && valid) {
                 Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

			moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;
                    break;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move bishop problem realloc 2 \n");
                    cfree(moves.position);
                    break;

                }
		}
		else if(friend){
            break;

		}

    }
	
		
	/*diagonal down left*/
		for(int i = 0 ; piece->position.x + i < BOARD_SIZE-1 &&
                        piece->position.y - i > 0 ; i++){

		Position pos ;
		pos.x = piece->position.x + i + 1 ;
		pos.y = piece->position.y - i - 1 ;

		bool valid = check_valid_position(pos); 
		bool friend = check_friend(piece->color,game,pos);
		bool enemy = check_enemy(piece->color,game,pos);
		if(!friend && !enemy && valid){
                Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move bishop problem realloc \n");
                    cfree(moves.position);
                    break;

                }

		}
		else if (enemy && valid ) {
                 Position * ptr_free = moves.position;
                if((ptr_free = realloc(moves.position ,(moves.number+1) * sizeof(Position) ) )!=NULL ){

                    moves.number++;
                    moves.position = ptr_free;
                    moves.position[moves.number-1] = pos;
                    break;

                }
                else{
		   MEMDEALLOC_DEBUG_POSITION++;
                    printf("move bishop problem realloc 2 \n");
                    cfree(moves.position);
                    break;

                }
		}
		else if(friend){
            break;
		}

    }
    return moves;

    }
    /*******************************************************************************************************************************************************************************************************/







 ERROR move_piece(Game* game, Piece** piece, Position pos){
    return move_temp(game,piece,pos);



}





/*******************************************************************************************************************************************************************************************************/
