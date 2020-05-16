///////////////////////////////////////////////////////////////////////////////
//  File    :   request.h
//  Brief   :   Defines the Bridges request object. The request object encodes
//              the HTTP request headers and parameters into a functional object
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_REQUEST_H
#define BRIDGES_REQUEST_H

#include <bridges/defs.h>

namespace bridges
{

class Request
{
public:
        
    Method  method  = INVALID;
    URI     target  = "";
    Headers headers = {};
    String  body    = "";
    Protocol_Version version = {0,0};
};

} // namespace bridges

#endif // BRIDGES_RESPONSE_H
