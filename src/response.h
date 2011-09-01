#ifndef __RESPONSE_H
#define __RESPONSE_H
#include <cstdio>
#include <string>
#include <fstream>
using namespace std;

class response {
 private:
  ifstream controllerfp;
  ifstream actionfp;
  ifstream mediafp;
  void render(char *, char *);
  void status(int, char *);
  void text(void);
  bool isbin(char *);
  char *getext(char *);
 public:
  string header;
  string ascii;
  char media[100];
  bool bin;
  bool load(char *, char *, char *);
  ~response(void);
};

#endif
