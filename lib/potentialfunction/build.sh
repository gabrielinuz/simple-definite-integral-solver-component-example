#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ libpotentialfunction.cpp -o libpotential.so 
