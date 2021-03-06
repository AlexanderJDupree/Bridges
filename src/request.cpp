///////////////////////////////////////////////////////////////////////////////
//  File    :   request.cpp
//  Brief   :   Bridges Request object implementation
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/utility.h>
#include <bridges/request.h>

namespace bridges
{

String Request::to_string() const 
{
    using namespace utility;
    
    return( format_request_line( method, target, version ) 
          + format_headers( headers )
          + CRLF
          + body
          );
}

} // namespace bridges
