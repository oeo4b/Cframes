#ifndef CLIENT_H
#define CLIENT_H

class client {
 public:
  int socket_con;
  client(int);
  void input(char*);
  void output(char *, char *);
  ~client(void);
};

#endif
