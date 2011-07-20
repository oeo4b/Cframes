#ifndef URI_H
#define URI_H

class uri {
 private:
  void getController(void);
  void getAction(void);
  void getParameters(void);
 public:
  char method[10];
  char url[50];
  char controller[25];
  char action[25];
  char parameters[500];
  void parse(char *);
  ~uri(void);
};

#endif
