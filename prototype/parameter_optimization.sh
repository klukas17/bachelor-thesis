#!/bin/bash

#################### INICIJALIZACIJA VARIJABLI ####################

REQUESTS="requests/train.txt"
PAGE_COUNT=1000
FRAME_COUNT=100
ITERATION_COUNT=20
ELITISM_COUNT=1

# PARAMETRI ALGORITMA
SELECTION=1 # 1 za generacijski algoritam, 2 za generacijski
MUTATION_RATE=5
POPULATION_SIZE=30
CODON_COUNT=20
MAX_NUMBER_OF_WRAPPING=5

# POSTAVLJANJE VARIJABLI
CURR=0
GENERATION=1

echo "Compiling code..."
g++ -c Unit.cpp Crossover.cpp Mutation.cpp GrammaticalEvolution.cpp Symbol.cpp Node.cpp Grammar.cpp Strategy.cpp
g++ -c init.cpp decode.cpp evolution.cpp
g++ Unit.o init.o -o init
g++ GrammaticalEvolution.o Symbol.o Node.o Grammar.o Unit.o decode.o -o decode
g++ evolution.o Unit.o Crossover.o Mutation.o -o evolution
echo "Compiling done!"

for MAX_NUMBER_OF_WRAPPING in 0 3 5
do
    echo ".................................................." >> logs_parameter_optimization.txt
    echo $(date) >> logs_parameter_optimization.txt

    if [ $SELECTION -eq 2 ]
    then
        ITERATION_COUNT=$((10 * $ITERATION_COUNT))
    fi

    for iter in {1..10}
    do
        GENERATION=1

        while [ $GENERATION -le ${ITERATION_COUNT} ]
        do
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

                # varijabla CURR se koristi samo kod steady-state algoritma
                CURR=`./evolution $POPULATION_SIZE $CODON_COUNT $MUTATION_RATE $ELITISM_COUNT $SELECTION`
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

            echo "ITERATION $iter: GENERATION $GENERATION"

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

            GENERATION=$((${GENERATION} + 1))

        done

        max=0

        for file in $(ls results); do a=$(cat results/$file); if [ $a -gt $max ]; then  max=$a; fi; done

        echo "ITERATION $iter: SELECTION = $SELECTION, MUTATION_RATE = $MUTATION_RATE, POPULATION_SIZE = $POPULATION_SIZE, CODON_COUNT = $CODON_COUNT, MAX_NUMBER_OF_WRAPPING = $MAX_NUMBER_OF_WRAPPING --- BEST = $max" >> logs_parameter_optimization.txt
    done
    echo $(date) >> logs_parameter_optimization.txt
    echo ".................................................." >> logs_parameter_optimization.txt
done
echo "" >> logs_parameter_optimization.txt
echo "==================================================" >> logs_parameter_optimization.txt
echo "" >> logs_parameter_optimization.txt