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

    Status status = Status::OK;

private:

};

} // namespace bridges

#endif // BRIDGES_RESPONSE_H
