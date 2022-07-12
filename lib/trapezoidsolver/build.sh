#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ libtrapezoidsolver.cpp -o libtrapezoidsolver.so
