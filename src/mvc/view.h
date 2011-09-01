#ifndef VIEW_H
#define VIEW_H
#include <string>
using namespace std;

class view {
 public:
  string ascii;
  view(char *, char *);
  string render(string, string);
  string renderaction(string);
  string interpret(string);
  ~view(void);
};

#endif
