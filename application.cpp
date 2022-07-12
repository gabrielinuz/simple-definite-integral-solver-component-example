/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#include <iostream>
#include <stdlib.h> 
#include <string>

#include <Compset/ComponentFactory.h>
#include <Compset/Component.h>
#include <Compset/Application.h>

using namespace std;

int main(int argc, char* argv[])
{
    if (1 < argc )
    {
        setenv("TERMINAL_QUERY_STRING", argv[1], 0);
    }

    ComponentFactory* componentFactory = new ComponentFactory();
    componentFactory->setType("Application");
    Component* applicationComponent = componentFactory->createFrom("./lib/libapplication");
    delete componentFactory;

    Application* application = ( (Application*) applicationComponent->getInstance() );
    application->run();
    applicationComponent->release();
    return 0;
}
