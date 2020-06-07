///////////////////////////////////////////////////////////////////////////////
//  File    :   response.h
//  Brief   :   Defines the Bridges response object
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_RESPONSE_H
#define BRIDGES_RESPONSE_H

#include <bridges/http_status.h>
#include <bridges/http_message.h>

namespace bridges
{

class Response : public HTTP_Message
{
public:
    Response( Status            status  = Status::Not_Implemented
            , Headers           headers = {} 
            , Protocol_Version  version = {0, 0}
            , String            body    = ""
            )
        : HTTP_Message( headers, body, version )
        , status( status )
        {}

    Status status = Status::Not_Implemented;

    String to_string() const override;

};

} // namespace bridges

#endif // BRIDGES_RESPONSE_H
