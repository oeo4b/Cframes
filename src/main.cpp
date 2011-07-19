/*
 * (c) 2011, Omar
 */

#include <iostream>
#include <cstdio>
#include "server.h"

int main(int argc, char **argv) {
  char buffer[8096];

  /* Start the server */
  server s;
  s.start(3000);

  /* Single-threaded forever loop to handle requests -- NOTE: eventually will have a daemon option -d */
  int i;
  for(i=0;i<20;i++) {
    std::cout << "Starting app..." << std::endl;
    s.app(s.wait());
    std::cout << "App closed." << std::endl;
  }
  s.stop();	
  return 0;
}

