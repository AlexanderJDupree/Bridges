///////////////////////////////////////////////////////////////////////////////
//  File    :   headers.h
//  Brief   :   Http headers abstraction
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_HEADERS_H
#define BRIDGES_HEADERS_H

#include <bridges/types.h>
#include <bridges/utility.h>

namespace bridges
{

struct case_insensitive_compare { 

    bool operator()(const String& lhs, const String& rhs) const {
        return std::lexicographical_compare(
            lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), 
            [](char c1, char c2){ return ::tolower(c1) < ::tolower(c2); }
            );
    }

};

class Headers 
{
public:

    using headers_t  = std::map<String, String, case_insensitive_compare>;

    Headers
        (
        headers_t&& data = {}
        )
    : data( data )
    {}

    // TODO: figure out how to order headers by category if possible
    headers_t data;

    void append(String&& field_name, String&& field_Value);

    Maybe<String> get(const String& field_name) const;

    bool contains(const String& field_name) const;

};


} //namespace bridges

#endif // BRIDGES_HEADERS_H
