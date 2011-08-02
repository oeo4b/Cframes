#ifndef RESPONSE_H
#define RESPONSE_H
#include <cstdio>

class response {
 private:
  void render(void);
  void status(int, char *);
  void text(void);
  bool isbin(char *);
  void error(int);
 public:
  char *header;
  char *ascii;
  bool bin;
  FILE *fp;
  bool load(char *, char *, char *);
  ~response(void);
};

#endif
