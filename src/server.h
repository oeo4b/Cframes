#ifndef SERVER_H
#define SERVER_H
#include <cstring>

class server {
  int socket_srvr;
  int socket_con;
  size_t length;
public:
  server(int);
  void receive(void);
  void send(void);
  ~server(void);
};

#endif
