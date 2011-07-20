#ifndef SERVER_H
#define SERVER_H

class server {
 public:
  int socket_srvr;
  void start(int);
  void stop(void);
};

#endif
