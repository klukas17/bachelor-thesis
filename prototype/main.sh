#!/bin/bash

#################### INICIJALIZACIJA VARIJABLI ####################

PAGE_COUNT=1000
FRAME_COUNT=200
POPULATION_SIZE=100
ITERATION_COUNT=1000
CODON_COUNT=20
MAX_NUMBER_OF_WRAPPING=2
ELITISM_COUNT=10
REQUESTS="requests/zahtjevi_treniranje.txt"
MUTATION_RATE=100

GENERATION=1

echo "Compiling code..."
g++ -c Unit.cpp Crossover.cpp Mutation.cpp GrammaticalEvolution.cpp Symbol.cpp Node.cpp Grammar.cpp Strategy.cpp
g++ -c init.cpp decode.cpp evolution.cpp
g++ Unit.o init.o -o init
g++ GrammaticalEvolution.o Symbol.o Node.o Grammar.o Unit.o decode.o -o decode
g++ evolution.o Unit.o Crossover.o Mutation.o -o evolution
echo "Compiling done!"

while [ $GENERATION -le ${ITERATION_COUNT} ]
do
    #read -p "Press enter to continue..."
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
        ./evolution $POPULATION_SIZE $CODON_COUNT $MUTATION_RATE $ELITISM_COUNT
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

    echo "GENERATION $GENERATION"

    if [ -d "results" ]
    then
        rm -r "results"
    fi
    mkdir "results"

    g++ -c GEStrategy.cpp run.cpp
    g++ Strategy.o GEStrategy.o run.o -o run
    ./run $POPULATION_SIZE $REQUESTS $PAGE_COUNT $FRAME_COUNT

    GENERATION=$((${GENERATION} + 1))

done