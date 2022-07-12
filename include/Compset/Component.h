/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>


class Component
{
    public:
        virtual ~Component(){}
        
        virtual bool implements(std::string interfaceName) = 0;
        virtual void* getInstance() = 0;
        virtual void release() = 0;
};

#endif // COMPONENT_H
