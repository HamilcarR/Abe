#!/bin/zsh



valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck --show-reachable=yes $1
