/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef COPONENTFACTORY_H
#define COPONENTFACTORY_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include "LibraryLoader.h"
#include "Component.h"

using namespace std;

class ComponentFactory
{
    public:
        ComponentFactory();
        ComponentFactory(string interfaceName);
 		void setType(string interfaceName);
        virtual ~ComponentFactory();
        Component* createFrom(string path);

    private:
    	string m_interfaceName;
};

ComponentFactory::ComponentFactory()
{
    //ctor
    m_interfaceName = "";
}

ComponentFactory::~ComponentFactory()
{
    //dtor
}

ComponentFactory::ComponentFactory(string interfaceName)
{
    m_interfaceName = interfaceName;
}

void ComponentFactory::setType(string interfaceName)
{
    m_interfaceName = interfaceName;
}

Component* ComponentFactory::createFrom(string path)
{
    Component* component = NULL;
    bool notNullFactory; 

    //THE LOADER:
    LibraryLoader* loader = LibraryLoader::getInstance();

    //LOAD
    void* load = loader->loadLibrary(path);

    if(load)
    {
        typedef Component* ( *ComponentFactory ) ();
        ComponentFactory factory = ( ComponentFactory ) loader->getExternalFunction( "create" );

        if ( factory )
        {
            Component* createdComponent;
            notNullFactory = (createdComponent = factory());

            if ( notNullFactory )            
            {
                if(m_interfaceName != "")
                {
                    if(createdComponent->implements(m_interfaceName))
                    {
                        component = createdComponent;
                    }
                    else
                    {
                        cout << "Error: The component doesn't implement the "+m_interfaceName+" interface!" << endl;
                        exit(-1);
                    }
                }
                else
                {
                    cout << "Error: The component requires an interface!" << endl;
                    exit(-1);
                }
            }
            else
            {
                loader->freeLibrary();
                cout << "Error:  Failed creating a component from "
                        << path << ", null component." << endl;
                exit(-1);
            }

        }
        else
        {
            loader->freeLibrary();
            cout << "Error:  Failed creating a component from "
                    << path << ", there is no external function \"create(void)\"." << endl;
            exit(-1);
        }
    }
    else
    {
        cout << "Error: Failed to load the library: " << path << endl;
        exit(-1);
    }

    return component;
}

#endif // COPONENTFACTORY_H
