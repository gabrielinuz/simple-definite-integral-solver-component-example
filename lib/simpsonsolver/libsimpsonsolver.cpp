/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#include <iostream>
#include <cmath>

#include <unordered_map>
#include <list>
#include <string>

#include <Compset/Solver.h>
#include <Compset/Component.h>
#include <Compset/Function.h>

using namespace std;

class SimpsonSolver : public Solver, public Component
{
    public:
        SimpsonSolver();
        virtual ~SimpsonSolver();
        list<string> getParameterList();
        void setFunction(Component* functionComponent);
        double solve(unordered_map<string, string> parameters);

        //Component
        bool implements(string interfaceName);
        void* getInstance();
        void release();

    private:
        list<string> m_parameters_list;
        Component* m_functionComponent;
        Function* m_function;
        //Component
        int m_referenceCounter;
        bool m_implemented;
};

SimpsonSolver::SimpsonSolver() : m_referenceCounter(0)
{
    m_parameters_list.push_back("x0");
    m_parameters_list.push_back("x1");
    m_parameters_list.push_back("intervals");
}

SimpsonSolver::~SimpsonSolver()
{
    m_functionComponent->release();
}

list<string> SimpsonSolver::getParameterList()
{
    return m_parameters_list;
}

void SimpsonSolver::setFunction(Component* functionComponent)
{
    m_functionComponent = functionComponent;

    if(m_functionComponent->implements("Function"))
    {
        m_function = (Function*) m_functionComponent->getInstance();
    }
    else
    {
        cout << "Error: The component doesn't implement the Function interface!" << endl;
        exit(-1);
    }
}

double SimpsonSolver::solve(unordered_map<string, string> parameters)
{
    /*PARAMETERS*/
    /*:Declared variables*/
    list<string> functionParameterList;
    list<string> solverParameterList;
    unordered_map<string, double> functionParameters;
    unordered_map<string, double> solverParameters;
    /*:Declared variables*/

    /*Obtain Solver Input Parameters:*/
    solverParameterList = getParameterList();
    for (list<string>::iterator it = solverParameterList.begin(); it != solverParameterList.end(); ++it)
    {
        solverParameters[*it] = stod(parameters[*it]);
    }
    /*:Obtain Solver Input Parameters*/

    /*Obtain Function Input Parameters:*/
    functionParameterList = m_function->getParameterList();
    for (list<string>::iterator it = functionParameterList.begin(); it != functionParameterList.end(); ++it)
    {
        functionParameters[*it] = stod(parameters[*it]);
    }
    /*:Obtain Function Input Parameters*/
    /*PARAMETERS*/

    /**************************************************************************************************/

    /*Simpson's 1/3-Rule*/
    int i;
    double dx;
    double x;
    double area = 0;
    double I=0;
    double J=0;

    /*dx*/
    dx = (solverParameters["x1"] - solverParameters["x0"]) / solverParameters["intervals"];

    for(i=1;i<solverParameters["intervals"];i++)
    {
        x = solverParameters["x0"] + i * dx;
        if((i%2)!=0)
        {
            I= I + abs(m_function->evaluate(functionParameters, x)) ;
        }
    }

    for(i=2;i<solverParameters["intervals"]-1;i++)
    {
        x = solverParameters["x0"] + i * dx;
        if((i%2)==0)
        {
            J= J + abs(m_function->evaluate(functionParameters, x)) ;
        }
    }

    area += abs( (dx/3)*(m_function->evaluate(functionParameters, solverParameters["x0"])+(4*I)+(2*J)+m_function->evaluate(functionParameters, solverParameters["x1"]) ) );
    /*Simpson's 1/3-Rule*/

    return area;
}

//Component
bool SimpsonSolver::implements(string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "Solver") ?
        m_implemented = true
            : m_implemented = false;
}

void* SimpsonSolver::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void SimpsonSolver::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new SimpsonSolver;
}
