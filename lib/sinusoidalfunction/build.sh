#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ libsinusoidalfunction.cpp -o libsinusoidal.so 
