///////////////////////////////////////////////////////////////////////////////
//  File    :   main.cpp
//  Brief   :   Entry Point for Bridges HTTP server
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

// Possible values for `ai_flags' field in `addrinfo' structure.  
//# define AI_PASSIVE	0x0001	// Socket address is intended for `bind'.  
//# define AI_CANONNAME	0x0002	// Request for canonical name.  
//# define AI_NUMERICHOST	0x0004	// Don't use name resolution.  
//# define AI_V4MAPPED	0x0008	/* IPv4 mapped addresses are acceptable.  
//# define AI_ALL		0x0010	/* Return IPv4 mapped and IPv6 addresses.  
//# define AI_ADDRCONFIG	0x0020	/* Use configuration of this host to choose
				   //returned address type..  
//# ifdef __USE_GNU
//#  define AI_IDN	0x0040	/* IDN encode input (assuming it is encoded
				   //in the current locale's character set)
				   //before looking it up. 
//#  define AI_CANONIDN	0x0080	/* Translate canonical name from IDN format. 
//#  define AI_IDN_ALLOW_UNASSIGNED 
  //__glibc_macro_warning ("AI_IDN_ALLOW_UNASSIGNED is deprecated") 0x0100
//#  define AI_IDN_USE_STD3_ASCII_RULES 
  //__glibc_macro_warning ("AI_IDN_USE_STD3_ASCII_RULES is deprecated") 0x0200
//# endif
//# define AI_NUMERICSERV	0x0400	/* Don't use name resolution.  

#include <iostream>
#include <bridges/server.h>
#include <bridges/utility.h>

int main(int, char**)
{
    using namespace bridges;

    const std::string banner = "////////////////////////////////////////////////////////////////////////////////";

    std::cout << banner << std::endl;
    std::cout << "BRIDGES" << std::endl;
    std::cout << "version\t:\t" << BRIDGES_VERSION << std::endl;
    std::cout << "License\t:\tMIT\n" << std::endl;
    std::cout << "Copyright (c) 2020 Alexander DuPree" << std::endl;
    std::cout << banner << std::endl;

    std::cout << "\nStarting server on localhost:8000" << std::endl;

    Server server;

    server.listen( "localhost", 8000 , AI_PASSIVE);
}
