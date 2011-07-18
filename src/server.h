#ifndef SERVER_H
#define SERVER_H
#include <cstring>
#include <sys/socket.h>

class server {
  int socket_srvr;
  int socket_con;
  socklen_t length;
public:
  void start(int);
  void loop(int);
  void stop(void);
};

#endif
