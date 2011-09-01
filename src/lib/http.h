#ifndef HTTP_H
#define HTTP_H

/* */
namespace http {
  char *protocol = (char *)"HTTP/1.1";

  struct response {
    int lookup;
    int group;
    char *code;
    char *reason;
  } message [] = {
    {100, 1, (char *)"100", (char *)"Continue"},
    {101, 1, (char *)"101", (char *)"Switching Protocols"},

    {200, 2, (char *)"200", (char *)"OK"},
    {201, 2, (char *)"201", (char *)"Created"},
    {202, 2, (char *)"202", (char *)"Accepted"},
    {203, 2, (char *)"203", (char *)"Non-Authoritative Information"},
    {204, 2, (char *)"204", (char *)"No Content"},
    {205, 2, (char *)"205", (char *)"Reset Content"},
    {206, 2, (char *)"206", (char *)"Partial Content"},

    {300, 3, (char *)"300", (char *)"Multiple Choices"},
    {301, 3, (char *)"301", (char *)"Moved Permanently"},
    {302, 3, (char *)"302", (char *)"Found"},
    {303, 3, (char *)"303", (char *)"See Other"},
    {304, 3, (char *)"304", (char *)"Not Modified"},
    {305, 3, (char *)"305", (char *)"Use Proxy"},
    {307, 3, (char *)"307", (char *)"Temporary Redirect"},

    {400, 4, (char *)"400", (char *)"Bad Request"},
    {401, 4, (char *)"401", (char *)"Unauthorized"},
    {402, 4, (char *)"402", (char *)"Payment Required"},
    {403, 4, (char *)"403", (char *)"Forbidden"},
    {404, 4, (char *)"404", (char *)"Not Found"},
    {405, 4, (char *)"405", (char *)"Method Not Allowed"},
    {406, 4, (char *)"406", (char *)"Not Acceptable"},
    {407, 4, (char *)"407", (char *)"Proxy Authentication Required"},
    {408, 4, (char *)"408", (char *)"Request Time-out"},
    {409, 4, (char *)"409", (char *)"Conflict"},
    {410, 4, (char *)"410", (char *)"Gone"},
    {411, 4, (char *)"411", (char *)"Length Required"},
    {412, 4, (char *)"412", (char *)"Precondition Failed"},
    {413, 4, (char *)"413", (char *)"Request Entity Too Large"},
    {414, 4, (char *)"414", (char *)"Request-URI Too Large"},
    {415, 4, (char *)"415", (char *)"Unsupported Media Type"},
    {416, 4, (char *)"416", (char *)"Requested range not satisfiable"},
    {417, 4, (char *)"417", (char *)"Expectation Failed"},

    {500, 5, (char *)"500", (char *)"Internal Server Error"},
    {501, 5, (char *)"501", (char *)"Not Implemented"},
    {502, 5, (char *)"502", (char *)"Bad Gateway"},
    {503, 5, (char *)"503", (char *)"Service Unavailable"},
    {504, 5, (char *)"504", (char *)"Gateway Time-out"},
    {505, 5, (char *)"505", (char *)"HTTP Version not supported"},

    {0, 0, 0, 0}
  };

};

#endif
