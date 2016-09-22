all : 
	gcc -pthread -g -Wall -pedantic -O0 -std=c11 sources/*.c -o program
