///////////////////////////////////////////////////////////////////////////////
//  File    :   request.h
//  Brief   :   Defines the Bridges request object. The request object encodes
//              the HTTP request headers and parameters into a functional object
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_REQUEST_H
#define BRIDGES_REQUEST_H

#include <bridges/http_message.h>

namespace bridges
{

class Request : public HTTP_Message
{
public:

    Method  method  = INVALID;
    URI     target  = "";

};

} // namespace bridges

#endif // BRIDGES_RESPONSE_H
