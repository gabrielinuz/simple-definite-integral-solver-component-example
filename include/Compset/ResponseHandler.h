/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

#include <string>
#include <iostream>

using namespace std;

class ResponseHandler
{
    public:
        virtual ~ResponseHandler() {}
    	virtual void response(string type) = 0;
};

#endif // RESPONSEHANDLER_H
