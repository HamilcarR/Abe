all : 
	gcc -pthread -Wall -pedantic -std=c11 sources/*.c -o program
