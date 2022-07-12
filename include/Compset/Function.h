/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

using namespace std;

class Function
{
    public:
    	virtual ~Function(){}
		virtual list<string> getParameterList() = 0;
    	virtual double evaluate(unordered_map<string, double> parameters, double x) = 0;
};

#endif // FUNCTION_H
