#ifndef URI_H
#define URI_H

class uri {
 private:
  void getAction(void);
  void getController(void);
  void getParameters(void);
 public:
  char *action;
  char *controller;
  char *method;
  char *parameters;
  char *url;
  void parse(char *);
  ~uri(void);
};

#endif
