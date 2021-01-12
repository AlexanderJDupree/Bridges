///////////////////////////////////////////////////////////////////////////////
//  File    :   http_status.h
//  Brief   :   Defines enumerations for HTTP status
//  Author  :   Alexander DuPree
//  License :   MIT
///////////////////////////////////////////////////////////////////////////////

#ifndef BRIDGES_HTTP_STATUS_H
#define BRIDGES_HTTP_STATUS_H

#include <bridges/defs.h>

namespace bridges
{

enum Status
{
    // 1xx Informational Response
    Continue                        = 100,
    Switching_Protocols             = 101,
    Processing                      = 102,
    Early_Hints                     = 103,

    // 2xx Success
    OK                              = 200,
    Created                         = 201,
    Accepted                        = 202,
    Non_Authoritative_Information   = 203,
    No_Content                      = 204,
    Reset_Content                   = 205,
    Partial_Content                 = 206,
    Multi_Status                    = 207,
    Already_Reported                = 208,
    IM_Used                         = 226,

    // 3xx Redirection
    Multiple_Choices                = 300,
    Moved_Permanently               = 301,
    Found                           = 302,
    See_Other                       = 303,
    Not_Modified                    = 304,
    Use_Proxy                       = 305,
    Switch_Proxy                    = 306,
    Temporary_Redirect              = 307,
    Permanent_Redirect              = 308,

    // 4xx Client Errors
    Bad_Request                     = 400,
    Unauthorized                    = 401,
    Payment_Required                = 402,
    Forbidden                       = 403,
    Not_Found                       = 404,
    Method_Not_Allowed              = 405,
    Not_Acceptable                  = 406,
    Proxy_Authentication_Required   = 407,
    Request_Timeout                 = 408,
    Conflict                        = 409,
    Gone                            = 410,
    Length_Required                 = 411,
    Precondition_Failed             = 412,
    Payload_Too_Large               = 413,
    URI_Too_Long                    = 414,
    Unsupported_Media_Type          = 415,
    Range_Not_Satisfiable           = 416,
    Expectation_Failed              = 417,
    Im_A_Teapot                     = 418, 
    Misdirected_Request             = 421,
    Unprocessable_Entity            = 422,
    Locked                          = 423,
    Failed_Dependency               = 424,
    Too_Early                       = 425,
    Upgrade_Required                = 426,
    Precondition_Required           = 428,
    Too_Many_Requests               = 429,
    Request_Header_Fields_Too_Large = 421,
    Unavailable_For_Legal_Reasons   = 451,

    // 5xx Server Errors
    Internal_Server_Error           = 500,
    Not_Implemented                 = 501,
    Bad_Gateway                     = 502,
    Service_Unavailable             = 503,
    Gateway_Timeout                 = 504,
    HTTP_Version_Not_Supported      = 505,
    Variant_Also_Negotiates         = 506,
    Insufficient_Storage            = 507,
    Loop_Detected                   = 508,
    Not_Extended                    = 510,
    Network_Authentication_Required = 511,

};

static const std::unordered_map<Status, String> status_to_str_tbl
{
    // 1xx Informational Response
    { Status::Continue,                         "Continue"                      },
    { Status::Switching_Protocols,              "Switching Protocols"           },
    { Status::Processing,                       "Processing"                    },
    { Status::Early_Hints,                      "Early Hints"                   },

    // 2xx Success
    { Status::OK,                               "OK"                            },
    { Status::Created,                          "Created"                       },
    { Status::Accepted,                         "Accepted"                      },
    { Status::Non_Authoritative_Information,    "Non Authoritative Information" },
    { Status::No_Content,                       "No Content"                    },
    { Status::Reset_Content,                    "Reset Content"                 },
    { Status::Partial_Content,                  "Partial Content"               },
    { Status::Multi_Status,                     "Multi Status"                  },
    { Status::Already_Reported,                 "Already Reported"              },
    { Status::IM_Used,                          "IM Used"                       },

    // 3xx Redirection
    { Status::Multiple_Choices,                 "Multiple Choices"              },
    { Status::Moved_Permanently,                "Moved Permanently"             },
    { Status::Found,                            "Found"                         },
    { Status::See_Other,                        "See Other"                     },
    { Status::Not_Modified,                     "Not Modified"                  },
    { Status::Use_Proxy,                        "Use Proxy"                     },
    { Status::Switch_Proxy,                     "Switch Proxy"                  },
    { Status::Temporary_Redirect,               "Temporary Redirect"            },
    { Status::Permanent_Redirect,               "Permanent Redirect"            },

    // 4xx Client Errors
    { Status::Bad_Request,                      "Bad Request"                   },
    { Status::Unauthorized,                     "Unauthorized"                  },
    { Status::Payment_Required,                 "Payment Required"              },
    { Status::Forbidden,                        "Forbidden"                     },
    { Status::Not_Found,                        "Not Found"                     },
    { Status::Method_Not_Allowed,               "Method Not Allowed"            },
    { Status::Not_Acceptable,                   "Not Acceptable"                },
    { Status::Proxy_Authentication_Required,    "Proxy Authentication Required" },
    { Status::Request_Timeout,                  "Request Timeout"               },
    { Status::Conflict,                         "Conflict"                      },
    { Status::Gone,                             "Gone"                          },
    { Status::Length_Required,                  "Length Required"               },
    { Status::Precondition_Failed,              "Precondition Failed"           },
    { Status::Payload_Too_Large,                "Payload Too Large"             },
    { Status::URI_Too_Long,                     "URI Too Long"                  },
    { Status::Unsupported_Media_Type,           "Unsupported Media Type"        },
    { Status::Range_Not_Satisfiable,            "Range Not Satisfiable"         },
    { Status::Expectation_Failed,               "Expectation Failed"            },
    { Status::Im_A_Teapot,                      "Im A Teapot"                   },
    { Status::Misdirected_Request,              "Misdirected Request"           },
    { Status::Unprocessable_Entity,             "Unprocessable Entity"          },
    { Status::Locked,                           "Locked"                        },
    { Status::Failed_Dependency,                "Failed Dependency"             },
    { Status::Too_Early,                        "Too Early"                     },
    { Status::Upgrade_Required,                 "Upgrade Required"              },
    { Status::Precondition_Required,            "Precondition Required"         },
    { Status::Too_Many_Requests,                "Too Many Requests"             },
    { Status::Request_Header_Fields_Too_Large,  "Request Header Fields Too Large"},
    { Status::Unavailable_For_Legal_Reasons,    "Unavailable For Legal Reasons" },

    // 5xx Server Errors
    { Status::Internal_Server_Error,            "Internal Server Error"         },
    { Status::Not_Implemented,                  "Not Implemented"               },
    { Status::Bad_Gateway,                      "Bad Gateway"                   },
    { Status::Service_Unavailable,              "Service Unavailable"           },
    { Status::Gateway_Timeout,                  "Gateway Timeout"               },
    { Status::HTTP_Version_Not_Supported,       "HTTP Version Not Supported"    },
    { Status::Variant_Also_Negotiates,          "Variant Also Negotiates"       },
    { Status::Insufficient_Storage,             "Insufficient Storage"          },
    { Status::Loop_Detected,                    "Loop Detected"                 },
    { Status::Not_Extended,                     "Not Extended"                  },
    { Status::Network_Authentication_Required,  "Network Authentication Required"},
};

} // namespace bridges

#endif // BRIDGES_HTTP_STATUS_H