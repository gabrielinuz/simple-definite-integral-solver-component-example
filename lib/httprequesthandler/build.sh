#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ libhttprequesthandler.cpp -o librequesthandler.so 
