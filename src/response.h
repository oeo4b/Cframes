#ifndef RESPONSE_H
#define RESPONSE_H
#include <cstdio>

class response {
 public:
  char *header;
  char *data;
  bool load(char *, char *, char *);
  ~response(void);
};

#endif
