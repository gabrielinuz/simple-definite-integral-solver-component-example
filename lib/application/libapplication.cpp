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

#include <Compset/Application.h>
#include <Compset/RequestHandler.h>
#include <Compset/Solver.h>
#include <Compset/Component.h>
#include <Compset/Function.h>
#include <Compset/ComponentFactory.h>

using namespace std;

class ApplicationLib : public Application, public Component
{
    public:
        ApplicationLib();
        virtual ~ApplicationLib();
        int run();

        //Component
        bool implements(string interfaceName);
        void* getInstance();
        void release();

    private:
        //Component
        int m_referenceCounter;
        bool m_implemented;
};

ApplicationLib::ApplicationLib() : m_referenceCounter(0)
{
}

ApplicationLib::~ApplicationLib(){}

int ApplicationLib::run()
{
    /*CREATION OF COMPONENT FACTORY*/
    ComponentFactory* componentFactory = new ComponentFactory();

/********************************************************************************************/

/*REQUEST ANALIZER COMPONENT SECTION*/
    componentFactory->setType("RequestHandler");
    Component* requestHandlerComponent = componentFactory->createFrom("./lib/librequesthandler");
    
    /*INSTANCE*/
    RequestHandler* requestHandler = ( (RequestHandler*) requestHandlerComponent->getInstance() );

    /*USE COMPONENT*/
    unordered_map<string, string> requestMap = requestHandler->getRequestMap();
/*REQUEST ANALIZER COMPONENT SECTION*/

/********************************************************************************************/ 

/********************************************************************************************/

/*SOLVER COMPONENT SECTION*/
    componentFactory->setType("Solver");

    Component* solverComponent = componentFactory->createFrom("./lib/lib" + requestMap["solver_name"] + "solver");
    
    Solver* solver = ( (Solver*) solverComponent->getInstance() );

    /*COMPOSITION OF SOLVER COMPONENT SECTION*/
    componentFactory->setType("Function");
    Component* functionComponent = componentFactory->createFrom("./lib/lib" + requestMap["function_name"]);
    solver->setFunction(functionComponent);
    /*COMPOSITION OF SOLVER COMPONENT SECTION*/
/*SOLVER COMPONENT SECTION*/

/********************************************************************************************/    



/********************************************************************************************/
    /*DELETION OF COMPONENT FACTORY*/
    delete componentFactory;
/********************************************************************************************/

    /*Declared variables:*/
    double result;

    /*Use solver:*/
    result = solver->solve(requestMap);
    /*:Use solver*/

    /*Result*/
    string strResult = to_string(result);
    string jsonOut;
    jsonOut = "Content-type: application/json; charset=utf-8\n\n";
    jsonOut += "{\"result\": \""+strResult+"\"}";

    cout << jsonOut;

    /*Release Components*/
    solverComponent->release();
    requestHandlerComponent->release();

    return 0;
}

//Component
bool ApplicationLib::implements(string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "Application") ?
        m_implemented = true
            : m_implemented = false;
}

void* ApplicationLib::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void ApplicationLib::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new ApplicationLib;
}
