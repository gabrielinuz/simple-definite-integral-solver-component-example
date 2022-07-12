/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class RequestHandler
{
    public:
        virtual ~RequestHandler() {}
    	virtual unordered_map<string, string> getRequestMap() = 0;
};

#endif // REQUESTHANDLER_H
