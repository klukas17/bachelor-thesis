#!/bin/bash

#################### INICIJALIZACIJA VARIJABLI ####################

PAGE_COUNT=1000
FRAME_COUNT=500
POPULATION_SIZE=50
ITERATION_COUNT=100
CODON_COUNT=50

#################### STVARANJE NASUMIČNE POČETNE GENERACIJE ####################

if [ -d "solutions" ]
then
    rm -r "solutions"
fi
mkdir solutions

g++ -c Unit.cpp
g++ -c init.cpp
g++ Unit.o init.o -o init
./init $POPULATION_SIZE $CODON_COUNT

#################### DEKODIRANJE POČETNE GENERACIJE ####################

g++ -c GrammaticalEvolution.cpp
g++ -c Symbol.cpp
g++ -c Node.cpp
g++ -c Grammar.cpp
g++ -c decode.cpp
g++ GrammaticalEvolution.o Symbol.o Node.o Grammar.o Unit.o decode.o -o decode
./decode $POPULATION_SIZE $CODON_COUNT