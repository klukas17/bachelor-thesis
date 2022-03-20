#!/bin/bash

g++ -std=c++17 -Wall -Wextra -g -c *.cpp
g++ -std=c++17 -Wall -Wextra -g *.o -o solution
./solution
rm *.o solution