/*
 (c) 2011, Omar

 */

#include "server.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER 10000

void server::start(int port) {
  /* Create the socket */
  static struct sockaddr_in server_addr;

  socket_srvr = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(port);
  
  bind(socket_srvr, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(socket_srvr, 64);
}

void server::stop() {
  close(socket_srvr);
}
