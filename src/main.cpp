/*
 * (c) 2011, Omar
 */

#include <iostream>
#include <cstdio>
#include <string>
#include "server.h"
#include "uri.h"
#include "response.h"

#define MAX_BUF 10000

void out(std::string send) {
  std::cout << send;
}

int main(int argc, char **argv) {
  /* Start the server */
  out("Starting cframes server...");
  server s;
  s.start(3000);
  out("OK\n");

  /* Single-threaded forever loop to handle requests -- NOTE: eventually will have a daemon option -d */
  int i;
  for(i=0;i<20;i++) {
    int client;
    uri u;
    response r;
    char *request;
    request = new char[MAX_BUF];

    client = s.wait();
    s.input(client, request);
    u.parse(request);  
    r.load(u.url, u.controller, u.action);

    out("Sending data..............");
    s.output(client, r.header, r.data);
    out("OK\n");

    out("Closing communication.....");
    s.end(client);
    out("OK\n");

    delete [] request;
  }
  s.finish();
	
  return 0;
}

