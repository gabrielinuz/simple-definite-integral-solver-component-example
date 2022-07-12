/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef SOLVER_H
#define SOLVER_H

#include <Compset/Component.h>
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

class Solver
{
    public:
        virtual ~Solver(){}
        virtual list<string> getParameterList() = 0;
        virtual void setFunction(Component* functionComponent) = 0;
        virtual double solve(unordered_map<string, string> parameters) = 0;
};

#endif // SOLVER_H
