/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

#include <Compset/Component.h>
#include <Compset/RequestHandler.h>
 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <regex>//FOR QUERY_STRING VALIDATION
#include <sstream>//FOR M_EXPLODE()

using namespace std;

class HttpRequestHandler : public RequestHandler, public Component
{
    public:
        HttpRequestHandler();
        virtual ~HttpRequestHandler();

        //RequestHandler
        unordered_map<string, string> getRequestMap();

        //Component
        bool implements(string interfaceName);
        void* getInstance();
        void release();

    private:
        string m_decode(string &input);
        vector<string> m_explode(string const &input, char delimiter);
        string m_getRequestParameters();

        //Component
        int m_referenceCounter;
        bool m_implemented;
};

HttpRequestHandler::HttpRequestHandler() : m_referenceCounter(0) {}

HttpRequestHandler::~HttpRequestHandler() {}

//Thanks Tominko...
string HttpRequestHandler::m_decode(string &input)
{
    string ret;
    char ch;
    unsigned int i;
    unsigned int ii;
    
    for (i=0; i<input.length(); i++)
    {
        if (int(input[i])==37)
        {
            sscanf(input.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else
        {
            ret+=input[i];
        }
    }
    return (ret);
}

vector<string> HttpRequestHandler::m_explode(string const &input, char delimiter)
{
    vector<string> result;
    istringstream iss(input);

    for (string token; getline(iss, token, delimiter); )
    {
        result.push_back(move(token));
    }

    return result;
}

string HttpRequestHandler::m_getRequestParameters()
{
    string requestParameters = "";

    if(getenv("REQUEST_METHOD") == NULL && getenv("TERMINAL_QUERY_STRING") == NULL)
    {
        cout << "The request method is null" << endl;
        exit(-1);
    }    
    if(getenv("REQUEST_METHOD") == NULL && getenv("TERMINAL_QUERY_STRING") != NULL)
    {
        string input = string(getenv("TERMINAL_QUERY_STRING"));
        bool isAQueryString = regex_match (input , regex("^([^=]+=[^=]+&)+[^=]+(=[^=]+)?$"));
        
        if (isAQueryString)
        {
            requestParameters = input;
        }
        else
        {
            cout << "The request is not a QUERY_STRING" << endl;
            exit(-1);
        } 
    }
    else
    {
        string requestMethod = string(getenv("REQUEST_METHOD"));

        if(requestMethod == "GET") { requestParameters = string(getenv("QUERY_STRING")); }

        if(requestMethod == "POST") { cin >> requestParameters; }
    }

    return requestParameters;
}

unordered_map<string, string> HttpRequestHandler::getRequestMap()
{
    string requestParameters = m_getRequestParameters();
    vector<string> keysWithValues = m_explode( m_decode(requestParameters), '&' );
    vector<string> keysAndValues;
    vector<string>::iterator i;

    int aux = 0;
    unordered_map<string, string> requestMap;

    for(i = keysWithValues.begin(); i != keysWithValues.end(); i++)
    {
        keysAndValues = m_explode( keysWithValues[aux], '=' );
        requestMap[keysAndValues[0]] = keysAndValues[1];
        aux++;
    }

    return requestMap;
}

//Component
bool HttpRequestHandler::implements(string interfaceName)
{
    return (interfaceName == "Component" || interfaceName == "RequestHandler") ?
        m_implemented = true
            : m_implemented = false;
}

void* HttpRequestHandler::getInstance()
{
    if(m_implemented) {  m_referenceCounter++;  return this; }
    return NULL;
}

void HttpRequestHandler::release()
{
    m_referenceCounter--;
    if(m_referenceCounter <= 0) delete this;
}

extern "C" Component* create();

Component* create()
{
    return (Component*) new HttpRequestHandler;
}
