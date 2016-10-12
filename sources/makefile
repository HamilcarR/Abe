CC=gcc
CFLAGS=-Wall -pthread -g -O3 -std=c11
EXEC=program
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
EXDIR=../
all : $(EXEC)
	mv $(EXEC) ../

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean


clean :
	rm -r *.o



























