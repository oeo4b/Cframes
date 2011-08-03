#include "view.h"
#include <iostream>
#include <cstdio>

view::view(char *controller, char *action) {
  /* Load the properties from the action */

}

void view::render(char *layout) {
  /* This method replaces all */

  ascii = new char[25];
  sprintf(ascii, "hello...");
}

view::~view(void) {
  delete [] ascii;
}
