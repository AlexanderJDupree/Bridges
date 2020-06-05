///////////////////////////////////////////////////////////////////////////////
//  File    :   http_message.h
//  Brief   :   Defines the basic structure of an http message. Inherited by
//              request and response classes
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_HTTP_MESSAGE_H
#define BRIDGES_HTTP_MESSAGE_H

#include <bridges/types.h>
#include <bridges/headers.h>

namespace bridges
{

class HTTP_Message
{
public:

    Headers headers = {};
    String  body    = "";
    Protocol_Version version = {0,0};

    virtual String to_string() const = 0;

    operator String()const { return to_string(); }
};

} // namespace bridges

#endif // BRIDGES_HTTP_MESSAGE_H
