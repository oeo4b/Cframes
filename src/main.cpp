/*
 * (c) 2011, Omar
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <cstring>
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
  clock_t start, end;
  uri u;
  response r;
  char request[MAX_BUF];

  /* Wait for request */
  client c(s.socket_srvr);

  /* Start the timer */
  start = clock();

  /* What does the client want? */
  c.input(request);

  /* Parse and load the request */
  u.parse(request);
  r.load(u.url, u.controller, u.action);

  /* Send the data */
  c.output(r.header, r.bin, r.ascii, r.media);

  /* Timer */
  out("\nCompleted in:\t");
  end = clock();
  std::cout << (float)1000*((float)end-(float)start)/(float)CLOCKS_PER_SEC;
  out(" ms\n\n");

  return true;
}

int main(int argc, char **argv) {
  /* Program start */
  /*
   * 
   *
   */
  int i;
  int port = 5000;
  char *bind = (char *)"0.0.0.0";
  bool daemon = false;

  /* Help info */
  for(i=0;i<argc;i++) {
    if(strcmp(argv[i],"-h")==0||strcmp(argv[i],"--help")==0) {
      out("Usage: cframes [options]\n");
      out("\t-p, --port PORT\tBind server socket to specified PORT\n");
      out("\t\t\tDefault: 5000\n");
      out("\t-b, --bind IP\tBind server to specified IP\n");
      out("\t\t\tDefault: 0.0.0.0\n");
      out("\t-d, --daemon\tForks server process\n");
      out("\t-h, --help\tDisplay this help and exit\n");
      out("\t-v, --version\tDisplay version information and exit\n");
      return 0;
    }
  }

  /* Version info */
  for(i=0;i<argc;i++) {
    if(strcmp(argv[i],"-v")==0||strcmp(argv[i],"--version")==0) {
      out("cframes 1.0.1\n");
      return 0;
    }
  }

  /* Program arguments */
  for(i=0;i<argc;i++) {
    if(strcmp(argv[i],"-p")==0||strcmp(argv[i],"--port")==0) {
      port = (int)argv[i+1];
    }
    if(strcmp(argv[i],"-b")==0||strcmp(argv[i],"--bind")==0) {
      bind = (char *)argv[i+1];
    }
    if(strcmp(argv[i],"-d")==0||strcmp(argv[i],"--daemon")==0) {
      daemon = true;
    }
  }

  /* Start the server */
  out("Starting cframes server...........");
  s.start(port);
  out("OK\n");
  out("Listening on http://");
  out(bind);out(":");out("5000");out("\n\n");

  /* Single-threaded forever loop to handle requests -- NOTE: eventually will have a daemon option -d */
  for(i=0;i<50;i++) { www(); }

  /* Stop the server */
  s.stop();
	
  return 0;
}

