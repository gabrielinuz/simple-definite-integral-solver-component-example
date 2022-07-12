/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

using namespace std;

class Application
{
    public:
    	virtual ~Application(){}
		virtual int run() = 0;
};

#endif // APPLICATION_H
