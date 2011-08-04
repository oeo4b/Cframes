/*
 * (c) 2011, Omar
 */

#include <iostream>
#include <cstdio>
#include <string>
#include "server.h"
#include "client.h"
#include "uri.h"
#include "response.h"

#define MAX_BUF 10000
server s;

void out(std::string send) {
  std::cout << send;
}

bool www(void) {
  /* Main client-server communication function */
  uri u;
  response r;
  char request[MAX_BUF];

  /* Wait for request */
  out("Ready.....................");
  client c(s.socket_srvr);
  out("OK\n");

  /* What does the client want? */
  c.input(request);

  /* Parse and load the request */
  u.parse(request);
  out("Controller: ");out(u.controller);out("\n");
  out("Action: ");out(u.action);out("\n");
  r.load(u.url, u.controller, u.action);

  out("Sending data..............");
  c.output(r.header, r.bin, r.ascii, r.media);
  out("OK\n");

  return true;
}

int main(int argc, char **argv) {
  /* Start the server */
  out("Starting cframes server...");
  s.start(5000);
  out("OK\n");

  /* Single-threaded forever loop to handle requests -- NOTE: eventually will have a daemon option -d */
  for(int i=0;i<20;i++) { www(); }

  /* Stop the server */
  s.stop();
	
  return 0;
}

