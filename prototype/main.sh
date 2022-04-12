#!/bin/bash

#################### INICIJALIZACIJA VARIJABLI ####################

PAGE_COUNT=1000
FRAME_COUNT=500
POPULATION_SIZE=50
ITERATION_COUNT=100
CODON_COUNT=50
MAX_NUMBER_OF_WRAPPING=5

#################### STVARANJE NASUMIČNE POČETNE GENERACIJE ####################

if [ -d "solutions" ]
then
    rm -r "solutions"
fi
mkdir "solutions"

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
echo "int function_1(GEStrategy* s) {" >> GeneratedStrategies.h
echo "  switch(s->strategy_index) {" >> GeneratedStrategies.h
for i in $(seq ${POPULATION_SIZE})
do
    echo "      case $((${i} - 1)): return f$((${i} - 1))(s);" >> GeneratedStrategies.h
done
echo "  }" >> GeneratedStrategies.h
echo "}" >> GeneratedStrategies.h
echo "int function_2(GEStrategy* s) {" >> GeneratedStrategies.h
echo "  switch(s->strategy_index) {" >> GeneratedStrategies.h
for i in $(seq ${POPULATION_SIZE})
do
    echo "      case $((${i} - 1)): g$((${i} - 1))(s); break;" >> GeneratedStrategies.h
done
echo "  }" >> GeneratedStrategies.h
echo "}" >> GeneratedStrategies.h
echo "}" >> GeneratedStrategies.h
