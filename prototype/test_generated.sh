#!/bin/bash

REQUESTS="requests/test.txt"
PAGE_COUNT=2646 # za testiranje je 2646

echo "Compiling code..."
g++ -c Unit.cpp Crossover.cpp Mutation.cpp GrammaticalEvolution.cpp Symbol.cpp Node.cpp Grammar.cpp Strategy.cpp FIFO.cpp LRU.cpp LFU.cpp OPT.cpp CLOCK.cpp
g++ -c init.cpp decode.cpp evolution.cpp test_heuristic_strategies.cpp
g++ Unit.o init.o -o init
g++ GrammaticalEvolution.o Symbol.o Node.o Grammar.o Unit.o decode.o -o decode
g++ evolution.o Unit.o Crossover.o Mutation.o -o evolution
g++ Strategy.o FIFO.o LRU.o LFU.o OPT.o CLOCK.o test_heuristic_strategies.o -o test_heuristic_strategies
echo "Compiling done!"

rm GeneratedStrategies.h

for FRAME_COUNT in 100 200 300 500
do
    for ITERATION in {1..10}
    do
        cp runs/$FRAME_COUNT/$ITERATION/200/strategies.cpp GeneratedStrategies.h
        g++ -c Strategy.cpp GEStrategy.cpp test_generated_strategy.cpp
        g++ Strategy.o GEStrategy.o test_generated_strategy.o -o test_generated_strategy
        for INDEX in {0..199}
        do
            RESULT=`./test_generated_strategy $REQUESTS $PAGE_COUNT $FRAME_COUNT $INDEX`
            echo "[$(date)] FRAME_COUNT = $FRAME_COUNT, ITERATION = $ITERATION, INDEX = $INDEX --- $RESULT" >> logs_generated_strategies_$FRAME_COUNT.txt
        done
    done
done