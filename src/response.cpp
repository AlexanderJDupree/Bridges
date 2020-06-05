///////////////////////////////////////////////////////////////////////////////
//  File    :   response.cpp
//  Brief   :   Bridges Request object implementation
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/utility.h>
#include <bridges/response.h>

namespace bridges
{

String Response::to_string() const 
{
    using namespace utility;

    return( format_status_line( version, status )
          + format_headers( headers )
          + CRLF
          + body
          );
}

} // namespace bridges
