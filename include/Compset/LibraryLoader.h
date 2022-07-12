/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#ifndef LIBRARYLOADER_H
#define LIBRARYLOADER_H

#ifdef __unix__
    #define RTLD_LAZY   1
    #define RTLD_NOW    2
    #define RTLD_GLOBAL 4
    #include "dlfcn.h"

#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#endif // defined

#include <string>
#include <iostream>

using namespace std;

class LibraryLoader
{
    public:
        virtual ~LibraryLoader();
        static LibraryLoader* getInstance();

        void* loadLibrary(string name);
        void* getExternalFunction(string name);
        bool freeLibrary();

    protected:
        LibraryLoader();

    private:
        static LibraryLoader* m_instance;
        void* m_library;
        void* m_method;
        bool m_freedom;
};

LibraryLoader* LibraryLoader::m_instance = 0;

LibraryLoader::LibraryLoader()
{
    //ctor
}

LibraryLoader::~LibraryLoader()
{
    //dtor
}

LibraryLoader* LibraryLoader::getInstance()
{
    if(m_instance == 0)
    {
        m_instance = new LibraryLoader();
    }
    return m_instance;
}

void* LibraryLoader::loadLibrary(string name)
{
    #ifdef __unix__
        name += ".so";
        m_library = dlopen(name.c_str(), RTLD_NOW);
    #elif defined(_WIN32) || defined(WIN32)
        name += ".dll";
        m_library = (void*) LoadLibrary(name.c_str());
    #endif // defined

    return m_library;
}

void* LibraryLoader::getExternalFunction(string name)
{
    #ifdef __unix__
        m_method = dlsym(m_library, name.c_str());
    #elif defined(_WIN32) || defined(WIN32)
        m_method = (void*) GetProcAddress((HINSTANCE)m_library, name.c_str());
    #endif // defined

    return m_method;
}

bool LibraryLoader::freeLibrary()
{
    #ifdef __unix__
        m_freedom = dlclose(m_library);
    #elif defined(_WIN32) || defined(WIN32)
        m_freedom = FreeLibrary((HINSTANCE)m_library);
    #endif // defined

    return m_freedom;
}

#endif // LIBRARYLOADER_H

