    #include "../headers/Config.h"
    #include <pthread.h>
    #include <malloc.h>
    #define BUFFER_SIZE 1024
    #define BUFFER0_SIZE 8





     typedef struct{
        Piece ** pieces;
        size_t number;
    }Piece_Array ;


    /*display chess in unicode in terminal */
    static const char* unicode[]={
    "\u2659",   //white pawn
    "\u2658",   //white knight
    "\u2656",   //white rook
    "\u2657",   //white bishop
    "\u2654",   //white king
    "\u2655",   //white queen
    "\u265F",   //black pawn
    "\u265E",   //black knight
    "\u265C",   //black rook
    "\u265D",   //black bishop
    "\u265A",   //black king
    "\u265B",   //black queen

    };



    /*********************************************************************************************************************************************************************************************************************/
    extern inline void print_piece(Piece* piece){
	printf("\n Type : %s \nPositions : %i  %i \n",piece_name[get_pieceID(*piece)],piece->position.x,piece->position.y);
    }

    /*********************************************************************************************************************************************************************************************************************/
    extern inline void read_pieces(Game* game){

        for(int i = 0  ; i < game->pieces_size ; i ++ ){
            print_piece(&(game->pieces[i]));

        }





    }


    /*********************************************************************************************************************************************************************************************************************/
    uint8_t get_pieceID(Piece piece){
        if (piece.color == WHITE){

                switch(piece.type){

                        case PAWN :
                            return PAWN_WHITE;
                        break;


                        case KING :
                            return KING_WHITE;
                        break;


                        case ROOK :
                            return ROOK_WHITE;
                        break;


                        case QUEEN :
                             return QUEEN_WHITE;
                        break;


                        case KNIGHT :
                            return KNIGHT_WHITE;
                        break;


                        case BISHOP :
                            return BISHOP_WHITE;
                        break;



                }

	}



            else{

                  switch(piece.type){


                        case PAWN :
                            return PAWN_BLACK;
                        break;


                        case KING :
                            return KING_BLACK;
                        break;


                        case ROOK :
                            return ROOK_BLACK;
                        break;


                        case QUEEN :
                             return QUEEN_BLACK;
                        break;


                        case KNIGHT :
                            return KNIGHT_BLACK;
                        break;


                        case BISHOP :
                            return BISHOP_BLACK;
                        break;


                }



    }
    }
    /*********************************************************************************************************************************************************************************************************************/
    bool check_valid_position(Position pos){
	if(pos.x>=BOARD_SIZE || pos.x < 0 || pos.y >= BOARD_SIZE || pos.y < 0 ){
		return false;
	}
	else
		return true;


    }
    /*********************************************************************************************************************************************************************************************************************/


     void free_game(Game * game){
	MEMDEALLOC_DEBUG_PIECE++;	
        free(game->pieces);
	MEMDEALLOC_DEBUG_GAME++;
        free(game);
    }
    /*********************************************************************************************************************************************************************************************************************/

    extern  inline void free_player(Player *player) {

        free(player->pieces);
	MEMDEALLOC_DEBUG_PIECE++;
	MEMDEALLOC_DEBUG_PLAYER++;
        cfree(player);

    }
    /*********************************************************************************************************************************************************************************************************************/

    extern inline void free_position(Position *position) {
	MEMDEALLOC_DEBUG_POSITION++;
        free(position) ;

    }
    /*********************************************************************************************************************************************************************************************************************/


     void read_stack(size_t * array , size_t size){
        size_t i = 0 ;
        for (i=0 ; i<size; i++){
            printf("%zi \n",array[i]);
        }
    }
    /*********************************************************************************************************************************************************************************************************************/

     void read_positions(Position ** positions,size_t size){
        size_t i = 0 ;
        for (i=0 ; i<size; i++){
            if(positions[i]->x == POSERR || positions[i]->y == POSERR){
                printf("NULL value : \n Error in .config file for %s coordinates",piece_name[i]);
                break;
                }
            else
            printf("%s have position (%i , %i) \n",piece_name[i],positions[i]->x,positions[i]->y);
        }
    }
    /*********************************************************************************************************************************************************************************************************************/


     void add_to_array(Piece* piece , int size ,Piece P ){
        if(add_p < size ) {
            piece[add_p].color = P.color;
            piece[add_p].position.x = P.position.x;
            piece[add_p].position.y = P.position.y;
            piece[add_p].type = P.type;
            add_p ++ ;
        }

    }


    /*********************************************************************************************************************************************************************************************************************/

         static void* read_file(void* filename) {
         char buffer[BUFFER_SIZE] ={" "};
        FILE* file = fopen((const char*)filename,"r");
        if(file==NULL){
            printf("file is not found ");
            return NULL;
            }
        else{
            char* temp = (char*) calloc(BUFFER_SIZE , sizeof(char));
	    if(temp == NULL){
		printf("\n read_file,config.c,temp == NULL" ) ; 
		return NULL ; 	

	    }
            if(fgets(buffer,BUFFER_SIZE,file) != NULL){
                strcat(temp,buffer);

            }
            int i = 2;
            while(fgets(buffer,BUFFER_SIZE ,file) !=  NULL){
                    void* ptr = NULL ;

                   if((ptr =(char*) realloc(temp,BUFFER_SIZE * i * sizeof(char))) !=NULL ){
                    temp = ptr;
                     strcat(temp,buffer);
                      i++;
                      ptr=NULL;
                   }
                   else{
                    printf("reallocation in read_file failed !");
                    free(temp) ;
		    break;
                   }




                }
	    fclose(file); 
            return (void*)temp;


            }
        }

    /*********************************************************************************************************************************************************************************************************************/

       extern inline  void print_board(Game* game){

        int i = 0 , j = 0 ;
        char display_board[BOARD_SIZE][BOARD_SIZE][BUFFER0_SIZE];
        char ret_l_b[BUFFER0_SIZE] = " # \n",black[BUFFER0_SIZE]=" # ",white[BUFFER0_SIZE]=" * ",ret_l_w[BUFFER0_SIZE] = " * \n";
        for(i = 0 ; i<BOARD_SIZE ; i++){

            for(j = 0  ; j < BOARD_SIZE ; j++){
                if(game->color_distrib[i][j] == BLACK){

                    if(j == BOARD_SIZE-1)
                      strcpy( display_board[i][j],ret_l_b) ;
                      else
                      strcpy( display_board[i][j], black);
                }
                   //display_board[i][j] = "#  ";
                else if (game ->color_distrib[i][j] == WHITE){

                    if(j == BOARD_SIZE-1)
                      strcpy( display_board[i][j],ret_l_w) ;
                      else
                      strcpy( display_board[i][j], white);

                }
                else
                    printf("chess colors not initialized");

            }


        }







        for(size_t i = 0 ; i < game->pieces_size ; i++){
            int8_t x = game->pieces[i].position.x;
            int8_t y = game->pieces[i].position.y;
                if(game->pieces[i].color == WHITE){


                            if(game->pieces[i].type == PAWN){
                                char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[PAWN_WHITE] ) ;
                                sprintf(temp1," %s ",unicode[PAWN_WHITE] ) ;

                              if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);


                            }
                            else if (game->pieces[i].type ==KNIGHT){
                                char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                               sprintf(temp," %s  \n",unicode[KNIGHT_WHITE] ) ;
                                sprintf(temp1," %s ",unicode[KNIGHT_WHITE] ) ;
                                if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);


                            }
                            else if (game->pieces[i].type == ROOK) {
                             char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[ROOK_WHITE] ) ;
                                 sprintf(temp1," %s ",unicode[ROOK_WHITE] ) ;


                              if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);
                            }
                            else if (game->pieces[i].type ==BISHOP) {
                            char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[BISHOP_WHITE] ) ;
                                 sprintf(temp1," %s ",unicode[BISHOP_WHITE] ) ;


                               if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);

                            }
                            else if (game->pieces[i].type ==KING) {
                            char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[KING_WHITE] ) ;
                                 sprintf(temp1," %s ",unicode[KING_WHITE] ) ;


                                if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);
                            }
                            else if (game->pieces[i].type ==QUEEN) {
                            char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[QUEEN_WHITE] ) ;
                                 sprintf(temp1," %s ",unicode[QUEEN_WHITE] ) ;

                                if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);
                            }



                            }



                else{



                             if (game->pieces[i].type ==PAWN) {
                            char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[PAWN_BLACK] ) ;
                                sprintf(temp1," %s ",unicode[PAWN_BLACK] ) ;
                              if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);
                            }
                            else if (game->pieces[i].type ==KNIGHT){
                            char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                               sprintf(temp," %s  \n",unicode[KNIGHT_BLACK] ) ;
                                sprintf(temp1," %s ",unicode[KNIGHT_BLACK] ) ;

                                if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);
                            }
                            else if (game->pieces[i].type ==ROOK) {
                            char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[ROOK_BLACK] ) ;
                                 sprintf(temp1," %s ",unicode[ROOK_BLACK] ) ;

                                 if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);
                            }
                            else if (game->pieces[i].type ==BISHOP) {
                            char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[BISHOP_BLACK] ) ;
                                 sprintf(temp1," %s ",unicode[BISHOP_BLACK] ) ;

                                if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);
                            }
                            else if (game->pieces[i].type ==KING) {
                            char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[KING_BLACK] ) ;
                                 sprintf(temp1," %s ",unicode[KING_BLACK] ) ;

                                 if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);
                            }
                            else if (game->pieces[i].type ==QUEEN) {
                            char temp[BUFFER0_SIZE] , temp1[BUFFER0_SIZE];
                                sprintf(temp," %s  \n",unicode[QUEEN_BLACK] ) ;
                                 sprintf(temp1," %s ",unicode[QUEEN_BLACK] ) ;

                                 if (strstr(display_board[x][y] , "\n") == NULL )
                                    strcpy(display_board[x][y],temp1);
                              else
                                    strcpy(display_board[x][y],temp);
                            }






                    }

        }



        for(int i=0 ; i< BOARD_SIZE ; i++){
            for(int j=0 ;j<BOARD_SIZE ; j++)
                printf("%s",display_board[i][j]);
        }
        size_t *stack = game->stack ;

        printf("\n\n");
        const char sep[]="----------------------------------------------------------------------------\n Stack : ";
        printf("%s",sep);
        for(int i = 0 ;i<MAX_PIECES;i++){
                for(uint8_t j =0 ; j < stack[i] ; j++){

                    switch(i){

                    case PAWN_WHITE :
                        printf("%s ",unicode[PAWN_WHITE]);

                    break;
                    case KNIGHT_WHITE :
                         printf("%s ",unicode[KNIGHT_WHITE]);
                    break;
                    case ROOK_WHITE :
                         printf("%s ",unicode[ROOK_WHITE]);
                    break;
                    case BISHOP_WHITE :
                         printf("%s ",unicode[BISHOP_WHITE]);
                    break;
                    case KING_WHITE :
                         printf("%s ",unicode[KING_WHITE]);
                    break;
                    case QUEEN_WHITE :
                         printf("%s ",unicode[QUEEN_WHITE]);
                    break;
                    case PAWN_BLACK :
                         printf("%s ",unicode[PAWN_BLACK]);
                    break;
                    case KNIGHT_BLACK :
                         printf("%s ",unicode[KNIGHT_BLACK]);
                    break;
                    case ROOK_BLACK :
                         printf("%s ",unicode[ROOK_BLACK]);
                    break;
                    case BISHOP_BLACK :
                         printf("%s ",unicode[BISHOP_BLACK]);
                    break;
                    case KING_BLACK :
                         printf("%s ",unicode[KING_BLACK]);
                    break;
                    case QUEEN_BLACK :
                         printf("%s ",unicode[QUEEN_BLACK]);
                    break;

                    }

                }


        }
        printf("\n\n");
        }

        /*********************************************************************************************************************************************************************************************************************/

        /*create an instance of Game by extracting it from a file */
        inline static Game* extract_pieces(char* board){
            Game* chess_board =(Game*) calloc(1,sizeof(Game)); /* TODO (hamilcar #4#) : free memory ! */
	    MEMALLOC_DEBUG_GAME++;
            if(chess_board == NULL){
                printf("Problem allocation fct extract_pieces");
            	
	    	return NULL;
            }
            char* c=strtok(board,"\n");
            size_t stack [MAX_PIECES]={0};
            size_t number_of_pieces = 0 ;
            Piece  *temp_pieces = calloc(1,sizeof(Piece)) ;
	    MEMALLOC_DEBUG_PIECE++;
            bool error = false;
            size_t i = 0 ;

            while(c!=NULL)
                {
                    if(error == true)
                        break;
                    if(strcmp((const char*) c,"-STACK:") == 0){

                    c=strtok(NULL,"\n");

                       while(strcmp((const char*)c,"-PARAMETERS:")!=0){

                            if(c[0] == 'W'){
                                if(c[1] == 'P')
                                    stack[PAWN_WHITE] ++ ;
                                else if(c[1] == 'C')
                                    stack[KNIGHT_WHITE] ++;
                                else if(c[1] == 'K')
                                    stack[KING_WHITE] ++;
                                else if(c[1] == 'Q')
                                    stack[QUEEN_WHITE] ++;
                                else if(c[1] == 'R')
                                    stack[ROOK_WHITE] ++;
                                else if(c[1] == 'B')
                                    stack[BISHOP_WHITE] ++;
                                else{
                                    error=true;
                                    printf("Error...I don't knuw huw 2 reed dat \"%c\" mu frund! \n goodbye! ",c[1]);
                                    break;
                                }

                                }
                            else if(c[0] == 'B'){
                                  if(c[1] == 'P')
                                    stack[PAWN_BLACK] ++ ;
                                    else if(c[1] == 'C')
                                        stack[KNIGHT_BLACK] ++;
                                    else if(c[1] == 'K')
                                        stack[KING_BLACK] ++;
                                    else if(c[1] == 'Q')
                                        stack[QUEEN_BLACK] ++;
                                    else if(c[1] == 'R')
                                        stack[ROOK_BLACK] ++;
                                    else if (c[1] == 'B')
                                        stack[BISHOP_BLACK] ++;
                                    else{
                                        error=true;
                                        printf("Error...I don't knuw huw 2 reed dat \"%c\" mu frund! \n goodbye! ",c[1]);
                                        break;
                                }
                            }
                            else{
                                    error=true;
                                    printf("Error...I don't knuw huw 2 reed dat \"%c\" mu frund! \n goodbye! ",c[0]);
                                    break;
                            }
                        c=strtok(NULL,"\n");
                       }

                    }
                    if(strcmp((const char*) c , "-PARAMETERS:") == 0){
                        c=strtok(NULL,"\n");
                        while(c!=NULL){

                            if(c[0] == 'W'){
                                 Piece P;
                                if(c[1] == 'P'){


                                    int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                    int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                     P.type = PAWN;
                                     P.color = WHITE;
                                     P.position.x=x;
                                     P.position.y=y;
                                     number_of_pieces ++ ;
                                }

                                else if (c[1] == 'K'){
                                     int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;      /*TODO : eliminates doubles */
                                    int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                     P.type = KING;
                                     P.color = WHITE;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;
                                }

                            else if (c[1] == 'Q'){
                               int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = QUEEN;
                                 P.color = WHITE;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;
                                }

                            else if (c[1] == 'C'){
                                int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = KNIGHT;
                                 P.color = WHITE;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;
                                }

                            else if (c[1] == 'R'){
                                 int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = ROOK;
                                 P.color = WHITE;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;
                                }

                            else if (c[1] == 'B'){
                                int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = BISHOP;
                                 P.color = WHITE;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;}

                            void* pointer_error_check = &temp_pieces;
                            if((pointer_error_check = realloc(temp_pieces,number_of_pieces * sizeof(Piece)))!=NULL) {
                                temp_pieces =(Piece*) pointer_error_check;
                                temp_pieces[number_of_pieces-1] = P ;


                            }
                            else{
                                printf("An error has occured while reallocating memory \n.");

				MEMDEALLOC_DEBUG_PIECE++; 
                                free(temp_pieces);
                            }


                            }

                        else if(c[0] == 'B'){
                                 Piece P;
                            if(c[1] == 'P'){
                               int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = PAWN;
                                 P.color = BLACK;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;}

                            else if (c[1] == 'K'){
                               int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = KING;
                                 P.color = BLACK;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;
                                }

                            else if (c[1] == 'Q'){
                                int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = QUEEN;
                                 P.color = BLACK;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;
                                 }

                            else if (c[1] == 'C'){
                                int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = KNIGHT;
                                 P.color = BLACK;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;}

                            else if (c[1] == 'R'){
                                int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = ROOK;
                                 P.color = BLACK;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;}

                            else if (c[1] == 'B'){
                                int x = c[2]>= '0' && c[2]<= '9' ? c[2]-'0' : POSERR;
                                int y = c[3] >= '0' && c[3] <= '9' ? c[3]-'0' : POSERR;

                                 P.type = BISHOP;
                                 P.color = BLACK;
                                 P.position.x=x;
                                 P.position.y=y;
                                 number_of_pieces ++ ;}

                           void* pointer_error_check = &temp_pieces;
                            if((pointer_error_check = realloc(temp_pieces,number_of_pieces * sizeof(Piece)))!=NULL){
                                temp_pieces =(Piece*) pointer_error_check;
                                temp_pieces[number_of_pieces-1] = P ;


                            }
                            else{
                                printf("An error has occured while reallocating memory \n.");
				MEMDEALLOC_DEBUG_PIECE++;

                                free(temp_pieces);
                            }

                            }


                            c=strtok(NULL,"\n");

                    }

                }

            }


    /*initializing all fields*/
    chess_board ->pieces_size = number_of_pieces;
    chess_board ->pieces = temp_pieces;

    for(i = 0 ; i < MAX_PIECES ; i++){
        chess_board ->stack[i] = stack[i];
    }



    size_t j=0 ;
    for(i = 0 ; i < BOARD_SIZE ; i++){
        for(j = 0 ;j < BOARD_SIZE ; j++){
            if( i % 2 == 0 )
                chess_board ->color_distrib[i][j] = j % 2 == 0 ? BLACK : WHITE;
            else
                chess_board ->color_distrib[i][j] = j % 2 == 0 ? WHITE : BLACK;
            }
        }



    return chess_board;


    }
    /*********************************************************************************************************************************************************************************************************************/

    static Game* init_blank_game(Game* game){
        for(int i = 0 ;i < BOARD_SIZE ; i++){
            for(int j = 0 ;j < BOARD_SIZE ; j++){
                if( i % 2 == 0 )
                    game ->color_distrib[i][j] = j % 2 == 0 ? BLACK : WHITE;
                else
                    game ->color_distrib[i][j] = j % 2 == 0 ? WHITE : BLACK;

            }
        }
        game->pieces = malloc(0);
	MEMALLOC_DEBUG_PIECE++;
        game->pieces_size = 0 ;
        for(int i = 0 ; i < MAX_PIECES ; i++)
            game->stack[i] = (size_t) 0 ;

        return game;

    }

    /*********************************************************************************************************************************************************************************************************************/

    static bool isValid(Game *game){

    Piece* P = game->pieces;

    bool black_king = false;
    bool white_king = false;
    for(size_t i = 0 ; i < game->pieces_size ; i++){
        if (P[i].type == KING && P[i].color == WHITE)
            white_king = true;
        if(P[i].type == KING && P[i].color == BLACK )
            black_king = true;

    }

    return black_king && white_king ;
    }

    /*********************************************************************************************************************************************************************************************************************/

     Game * init_board(const char* filename){
    pthread_t thread1 ;
    Game *game = (void*) 0 ;
    void* (*ptr_read_file)(void*) = &read_file;

    pthread_create(&thread1,NULL,ptr_read_file,(void*)filename);
    char *char_board ;

    pthread_join(thread1,(void*)&char_board);
    if(char_board != NULL)
        game=extract_pieces(char_board);
    else
        game= init_blank_game(game);


    if(!isValid(game)){
        printf("\nChess without kings...?\nyou don't believe in monarchy,do you ? \u2639  \n");
        free_game(game) ;
	MEMDEALLOC_DEBUG_GAME++ ; 
        return NULL;
    }

    free(char_board); 
    return game;


    }

    /*********************************************************************************************************************************************************************************************************************/



  static bool find_piece(Game* g , Piece *p ){
	for(int i = 0 ; i < g->pieces_size ; i ++){
		if(equal_piece (&(g->pieces[i]) , p)) 
			return true; 
	}

	return false;

  }








    /*********************************************************************************************************************************************************************************************************************/



   bool equal_game(Game *g1 , Game *g2){
	for(int i = 0 ; i < MAX_PIECES ; i++){
		if(g1->stack[i]!=g2->stack[i])
			return false;			
	}	
	if(g1->pieces_size != g2->pieces_size)
		return false; 
	else{
	   for(int i = 0 ; i < g1->pieces_size; i ++ ) {
		if( !find_piece(g2,&(g1->pieces[i]) ) )
			return false; 
		  }
	return true; 
	}
   }
   
       /*********************************************************************************************************************************************************************************************************************/


  bool equal_piece(Piece* p1, Piece* p2){
	if(p1->type != p2->type || p1->color != p2->color || p1->position.x != p2->position.x || p1->position.y != p2->position.y)		return false; 
	else
	      return true; 	

  }





    /*********************************************************************************************************************************************************************************************************************/


   Game* get_board_copy(Game* src){
	Game* copy = calloc(1,sizeof(Game));
        MEMALLOC_DEBUG_GAME++;	
	copy->pieces_size = src->pieces_size; 
	for(int i = 0 ; i < BOARD_SIZE ; i++){
		for(int j = 0 ; j < BOARD_SIZE ; j++)
			copy->color_distrib[i][j] = src->color_distrib[i][j];
	}		
	Piece* array = calloc(copy->pieces_size,sizeof(Piece));  	
	MEMALLOC_DEBUG_PIECE++;
	copy->pieces = array ; 
	assert(copy->pieces != NULL);
	for(int i = 0 ; i < src->pieces_size ; i ++ ){
		copy->pieces[i]=src->pieces[i];

	}	

	
	for(int i = 0 ; i < MAX_PIECES ; i ++ )
		copy->stack[i] = src->stack[i] ;

	
	return copy ; 

   }






















    /*********************************************************************************************************************************************************************************************************************/

