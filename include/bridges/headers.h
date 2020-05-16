///////////////////////////////////////////////////////////////////////////////
//  File    :   headers.h
//  Brief   :   Http headers abstraction
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_HEADERS_H
#define BRIDGES_HEADERS_H

#include <bridges/common.h>

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
    // TODO: add constructors

    void emplace(String&& field_name, String&& field_value);

    String& get(const String& field_name);
    const String& get(const String& field_name) const;

    bool contains(const String& field_name) const;

    String& operator[](const String& field_name);
    const String& operator[](const String& field_name) const;

private:

    using headers_t = std::multimap<String, String, case_insensitive_compare>;

    headers_t __headers;
};

} //namespace bridges

#endif // BRIDGES_HEADERS_H
