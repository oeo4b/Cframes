#ifndef SERVER_H
#define SERVER_H
#include <cstring>
#include <sys/socket.h>

class server {
  int socket_srvr;
public:
  void start(int);
  int wait(void);
  void app(int);
  void stop(void);
};

#endif
