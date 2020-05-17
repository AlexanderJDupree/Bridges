///////////////////////////////////////////////////////////////////////////////
//  File    :   headers.h
//  Brief   :   Http headers abstraction
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#include <bridges/headers.h>

namespace bridges 
{

void Headers::emplace(String&& field_name, String&& field_value)
{
    __headers.emplace(field_name, field_value);
}

// TODO: Multimap return a range an iterator to a range of values that match the key,
// We need to concatenate this values together as described in the standard
String& Headers::get(const String& field_name)
{
    return __headers.find(field_name)->second;
}

const String& Headers::get(const String& field_name) const
{
    return __headers.find(field_name)->second;
}

bool Headers::contains(const String& field_name) const
{
    return __headers.find(field_name) != __headers.end();
}

String& Headers::operator[](const String& field_name)
{
    return get(field_name);
}

const String& Headers::operator[](const String& field_name) const
{
    return get(field_name);
}

} // namespace bridges
