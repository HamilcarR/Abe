CC=gcc
CFLAGS=-Wall -pthread -g -O0 -std=c11
EXEC=program
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
EXDIR=../
all : $(EXEC)
	mv $(EXEC) ../

program : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)




clean :
	rm -r *.o



























