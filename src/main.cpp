/*
*
* (c) 2011, Omar O
*  
*
*/

#include <iostream>
#include "server.h"

int main(int argc, char **argv) {
  
  /* Single-threaded forever loop to handle requests -- NOTE: eventually will have a daemon option -d */
  server s(3000);
  s.receive();
  s.send();
	
  return 0;
}

