#ifndef EXTENSIONS_H
#define EXTENSIONS_H

struct extension {
  bool bin;
  char *type;
  char *http;  
} extensions [] = {
  {true, (char *)"gif", (char *)"image/gif"},
  {true, (char *)"jpg", (char *)"image/jpeg"},
  {true, (char *)"jpeg", (char *)"image/jpeg"},
  {true, (char *)"png", (char *)"image/png"},
  {false, (char *)"htm", (char *)"text/html"},
  {false, (char *)"html", (char *)"text/html"},
  {false, (char *)"txt", (char *)"text/html"},
  {false, (char *)"zip", (char *)"image/zip"},
  {true, (char *)"ico", (char *)"image/x-icon"},
  {0, 0, 0}  
};

#endif
