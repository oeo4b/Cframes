#ifndef URI_H
#define URI_H

class uri {
 public:
  char *action;
  char *controller;
  char *method;
  char *parameters;
  void parse(char *);
  ~uri();
};

#endif
