#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ libsimpsonsolver.cpp -o libsimpsonsolver.so
