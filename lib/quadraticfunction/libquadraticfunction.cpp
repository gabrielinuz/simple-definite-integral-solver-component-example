/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#include <Compset/Component.h>
#include <Compset/Function.h>
#include <iostream>
#include <cmath>

#include <unordered_map>
#include <list>
#include <string>

using namespace std;

class QuadraticFunction : public Function, public Component
{
    public:
        QuadraticFunction();
        virtual ~QuadraticFunction();
        //Function:
        list<string> getParameterList();
        double evaluate(unordered_map<string, double> parameters, double x);

        //Component:
        bool implements(string interfaceName);
        void* getInstance();
        void release();

    private:
        //Function:
        list<string> m_parametersList;
        //Component:
        int m_referenceCounter;
        bool m_implemented;
};

QuadraticFunction::QuadraticFunction() : m_referenceCounter(0)
{
    m_parametersList.push_back("a");
    m_parametersList.push_back("b");
    m_parametersList.push_back("c");
}

QuadraticFunction::~QuadraticFunction(){}

list<string> QuadraticFunction::getParameterList()
{
    return m_parametersList;
}

double QuadraticFunction::evaluate(unordered_map<string, double> parameters, double x)
{
    return parameters["a"] * (x * x) + (parameters["b"] * x) + parameters["c"];
}

//Component
bool QuadraticFunction::implements(string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "Function") ?
        m_implemented = true
            : m_implemented = false;
}

void* QuadraticFunction::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void QuadraticFunction::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new QuadraticFunction;
}
