#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ libhttpresponsehandler.cpp -o libresponsehandler.so 
