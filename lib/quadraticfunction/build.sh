#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ libquadraticfunction.cpp -o libquadratic.so 
