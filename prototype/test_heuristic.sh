#!/bin/bash

REQUESTS="requests/test.txt"
PAGE_COUNT=2646 # za testiranje je 2646
FRAME_COUNT=100

echo "Compiling code..."
g++ -c Unit.cpp Crossover.cpp Mutation.cpp GrammaticalEvolution.cpp Symbol.cpp Node.cpp Grammar.cpp Strategy.cpp FIFO.cpp LRU.cpp LFU.cpp OPT.cpp CLOCK.cpp
g++ -c init.cpp decode.cpp evolution.cpp test_heuristic_strategies.cpp
g++ Unit.o init.o -o init
g++ GrammaticalEvolution.o Symbol.o Node.o Grammar.o Unit.o decode.o -o decode
g++ evolution.o Unit.o Crossover.o Mutation.o -o evolution
g++ Strategy.o FIFO.o LRU.o LFU.o OPT.o CLOCK.o test_heuristic_strategies.o -o test_heuristic_strategies
echo "Compiling done!"

for FRAME_COUNT in 100 200 300 500
do
    echo "[$(date)] FRAME COUNT = $FRAME_COUNT" >> logs_heuristic_strategies.txt
    ./test_heuristic_strategies $REQUESTS $PAGE_COUNT $FRAME_COUNT >> logs_heuristic_strategies.txt
done