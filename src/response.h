#ifndef RESPONSE_H
#define RESPONSE_H
#include <cstdio>
#include <string>
#include <fstream>
using namespace std;

class response {
 private:
  void render(char *, char *);
  void status(char *, char *);
  void text(void);
  bool isbin(char *);
  void error(char *);
 public:
  string header;
  string ascii;
  char media[100];
  bool bin;
  ifstream fp;
  bool load(char *, char *, char *);
  ~response(void);
};

#endif
