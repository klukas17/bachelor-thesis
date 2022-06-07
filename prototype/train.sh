#!/bin/bash

REQUESTS="requests/train.txt"
PAGE_COUNT=1181 # za testiranje je 2646
FRAME_COUNT=100
ITERATION_COUNT=100
ELITISM_COUNT=1

# PARAMETRI ALGORITMA
SELECTION=1
MUTATION_RATE=20
POPULATION_SIZE=3
CODON_COUNT=20
MAX_NUMBER_OF_WRAPPING=5

echo "Compiling code..."
g++ -c Unit.cpp Crossover.cpp Mutation.cpp GrammaticalEvolution.cpp Symbol.cpp Node.cpp Grammar.cpp Strategy.cpp
g++ -c init.cpp decode.cpp evolution.cpp
g++ Unit.o init.o -o init
g++ GrammaticalEvolution.o Symbol.o Node.o Grammar.o Unit.o decode.o -o decode
g++ evolution.o Unit.o Crossover.o Mutation.o -o evolution
echo "Compiling done!"

if [ -d "runs" ]
then
    rm -r "runs"
fi
mkdir runs

mkdir runs/$FRAME_COUNT

for iter in {1..10}
do
    mkdir runs/$FRAME_COUNT/$iter

    GENERATION=1

    while [ $GENERATION -le $ITERATION_COUNT ]
    do

        mkdir runs/$FRAME_COUNT/$iter/$GENERATION

        if [ $GENERATION -eq 1 ]
        then

            #################### STVARANJE NASUMIČNE POČETNE GENERACIJE ####################

            if [ -d "solutions" ]
            then
                rm -r "solutions"
            fi
            mkdir "solutions"

            ./init $POPULATION_SIZE $CODON_COUNT
        else

            #################### STVARANJE NOVE GENERACIJE ####################

            ./evolution $POPULATION_SIZE $CODON_COUNT $MUTATION_RATE $ELITISM_COUNT $SELECTION
        fi


        #################### DEKODIRANJE TRENUTNE GENERACIJE ####################

        if [ -f "GeneratedStrategies.h" ]
        then 
            rm "GeneratedStrategies.h"
        fi
            touch "GeneratedStrategies.h"

        echo "#pragma once" >> GeneratedStrategies.h
        echo "" >> GeneratedStrategies.h
        echo '#include "GEStrategy.h"' >> GeneratedStrategies.h
        echo "" >> GeneratedStrategies.h
        echo "namespace GeneratedStrategies {" >> GeneratedStrategies.h
        ./decode $POPULATION_SIZE $CODON_COUNT $MAX_NUMBER_OF_WRAPPING >> GeneratedStrategies.h
        echo "int function(GEStrategy* s) {" >> GeneratedStrategies.h
        echo "  switch(s->strategy_index) {" >> GeneratedStrategies.h
        for i in $(seq ${POPULATION_SIZE})
        do
            echo "      case $((${i} - 1)): return f$((${i} - 1))(s);" >> GeneratedStrategies.h
        done
        echo "  }" >> GeneratedStrategies.h
        echo "  return 0;" >> GeneratedStrategies.h
        echo "}" >> GeneratedStrategies.h
        echo "}" >> GeneratedStrategies.h

        #################### POKRETANJE TRENUTNE GENERACIJE ####################

        g++ -c GEStrategy.cpp run.cpp
        g++ Strategy.o GEStrategy.o run.o -o run

        if [ $GENERATION -eq 1 -o $SELECTION -eq 1 ]
        then
            if [ -d "results" ]
            then
                rm -r "results"
            fi
            mkdir "results"
            ./run $POPULATION_SIZE $REQUESTS $PAGE_COUNT $FRAME_COUNT 1 0
        else
            ./run $POPULATION_SIZE $REQUESTS $PAGE_COUNT $FRAME_COUNT $SELECTION $CURR
        fi

        touch runs/$FRAME_COUNT/$iter/$GENERATION/strategies.cpp runs/$FRAME_COUNT/$iter/$GENERATION/fitness.txt
        cat GeneratedStrategies.h > runs/$FRAME_COUNT/$iter/$GENERATION/strategies.cpp
        l=()
        for file in $(ls results); do cat results/$file >> runs/$FRAME_COUNT/$iter/$GENERATION/fitness.txt; l+=$(cat results/$file);l+=" "; done

        echo "[$(date)] FRAME_COUNT $FRAME_COUNT, ITERATION $iter/10, GENERATION $GENERATION/$ITERATION_COUNT --- [ $l]" >> logs_train.txt

        GENERATION=$((${GENERATION} + 1))

    done
    
done
