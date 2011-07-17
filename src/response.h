#ifndef RESPONSE_H
#define RESPONSE_H

class response {
 public:
  char *header;
  char *html;
  bool load(char *, char *);
  ~response(void);
};

#endif
