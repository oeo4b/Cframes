/*
 (c) 2011, Omar

 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:

 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */

#include "server.h"
#include "uri.h"
#include "response.h"
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER 10000

void server::start(int port) {
  /* Create the socket */
  struct sockaddr_in server_addr;

  socket_srvr = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(port);
  
  bind(socket_srvr, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(socket_srvr, 64);
}

void server::loop(int hit) {
  /* 
   * In this loop:
   * Parse the request URI -> load controller/action (or defaults)
   * Write to the socket ->  client gets their response
   *
   */
  long read_client;
  char header[MAX_BUFFER-1];
  char request[MAX_BUFFER-1];
  uri u;
  response r;  
  bool what;

  /* Start accepting requests */
  struct sockaddr_in client_addr;

  length = sizeof(client_addr);
  socket_con = accept(socket_srvr, (struct sockaddr *)&client_addr, &length);
  
  read_client = read(socket_con, request, MAX_BUFFER);

  /* Interpret the request and create a response here */
  u.parse(request);

  what = r.load(u.controller, u.action);  
  write(socket_con, r.header, strlen(r.header));
  write(socket_con, r.html, strlen(r.html));
  
  /* Close the connection between the server and the client */
  close(socket_con);
}

void server::stop() {
  close(socket_srvr);
}
