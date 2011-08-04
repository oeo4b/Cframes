#ifndef CLIENT_H
#define CLIENT_H
#include <string>
using namespace std;

class client {
 public:
  int socket_con;
  client(int);
  void input(char *);
  void output(string, bool, string, char *);
  ~client(void);
};

#endif
