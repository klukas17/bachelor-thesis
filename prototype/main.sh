#!/bin/bash

if [ ! $# -eq 4 ]
then
    echo "Four arguments required!"
    exit 1
fi

PAGE_COUNT=$1
FRAME_COUNT=$2
POPULATION_SIZE=$3
ITERATION_COUNT=$4

g++ -std=c++17 -Wall -Wextra -g -c *.cpp
g++ -std=c++17 -Wall -Wextra -g *.o -o main
./main $PAGE_COUNT $FRAME_COUNT $POPULATION_SIZE
rm *.o main