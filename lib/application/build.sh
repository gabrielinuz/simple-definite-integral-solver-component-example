#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ libapplication.cpp -o libapplication.so
