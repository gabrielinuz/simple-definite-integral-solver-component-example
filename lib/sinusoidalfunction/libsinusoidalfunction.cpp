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

class SinusoidalFunction : public Function, public Component
{
    public:
        SinusoidalFunction();
        virtual ~SinusoidalFunction();
        list<string> getParameterList();
        double evaluate(unordered_map<string, double> parameters, double x);

        //Component
        bool implements(string interfaceName);
        void* getInstance();
        void release();

    private:
        list<string> m_parametersList;
        //Component
        int m_referenceCounter;
        bool m_implemented;
};

SinusoidalFunction::SinusoidalFunction() : m_referenceCounter(0) 
{
    m_parametersList.push_back("a");
    m_parametersList.push_back("k");    
}

SinusoidalFunction::~SinusoidalFunction(){}

list<string> SinusoidalFunction::getParameterList()
{
    return m_parametersList;
}

double SinusoidalFunction::evaluate(unordered_map<string, double> parameters, double x)
{
    return parameters["a"] * sin(parameters["k"] * x) ;
}

//Component
bool SinusoidalFunction::implements(string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "Function") ?
        m_implemented = true
            : m_implemented = false;
}

void* SinusoidalFunction::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void SinusoidalFunction::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new SinusoidalFunction;
}
