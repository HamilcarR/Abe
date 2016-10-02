#!/bin/zsh




valgrind --tool=drd --check-stack-var=yes --exclusive-threshold $1
