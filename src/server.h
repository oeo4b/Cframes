#ifndef SERVER_H
#define SERVER_H
#include <cstring>

class server {
  int socket_srvr;
  int socket_con;
  size_t length;
public:
  void start(int);
  void loop(int);
  void stop(void);
};

#endif
