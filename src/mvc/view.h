#ifndef VIEW_H
#define VIEW_H

class view {
 public:
  char *ascii;
  view(char *, char *);
  void render(char *);
  ~view(void);
};

#endif
