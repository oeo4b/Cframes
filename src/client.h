#ifndef CLIENT_H
#define CLIENT_H
#include <cstdio>

class client {
 public:
  int socket_con;
  client(int);
  void input(char*);
  void output(char *, bool, char *, FILE *);
  ~client(void);
};

#endif
