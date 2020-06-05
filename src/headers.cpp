///////////////////////////////////////////////////////////////////////////////
//  File    :   headers.h
//  Brief   :   Http headers abstraction
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/headers.h>

namespace bridges 
{

void Headers::append(String&& field_name, String&& field_value)
{
    // https://tools.ietf.org/html/rfc2616#section-4.2
    if(  data.find(field_name) != data.end() )
    {
        data[field_name] += fmt::format(", {}", field_value);
    }
    else
    {
        data.emplace(field_name, field_value);
    }
}

Maybe<String> Headers::get(const String& field_name) const
{
    try
    {
        return data.at(field_name);
    }
    catch(...)
    {
        return Nothing;
    }
}

bool Headers::contains(const String& field_name) const
{
    return data.find(field_name) != data.end();
}

} // namespace bridges
