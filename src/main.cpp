/*
*
* (c) 2011, OO
*  
*
*/

#include <iostream>
#include <cstdio>
#include "server.h"

int main(int argc, char **argv) {
  char buffer[8096];
  sprintf(buffer, "<html><head></head><body>Text</body></html>");

  /* Single-threaded forever loop to handle requests -- NOTE: eventually will have a daemon option -d */
  server s(3000);
  int i;
  for(i=0;i<5;i++) {
    s.start(buffer);
  }
  s.stop();	
  return 0;
}

