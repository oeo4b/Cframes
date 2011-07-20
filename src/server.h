#ifndef SERVER_H
#define SERVER_H
#include <cstring>
#include <sys/socket.h>

class server {
  int socket_srvr;
public:
  void start(int);
  int wait(void);
  void input(int, char*);
  void output(int, char *, char *);
  void end(int);
  void finish(void);
};

#endif
