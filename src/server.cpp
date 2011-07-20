/*
 (c) 2011, Omar

 */

#include "server.h"
#include <iostream>
#include <cstdio>
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

int server::wait(void) {
  /* 
   * Wait for a client...
   */
  int socket_con;
  socklen_t length;
  static struct sockaddr_in client_addr;

  length = sizeof(client_addr);
  socket_con = accept(socket_srvr, (struct sockaddr *)&client_addr, &length);

  return socket_con;
}

void server::input(int socket_con, char *request) {
  /* What does the client want? */
  long read_client;
  read_client = recv(socket_con, request, MAX_BUFFER, 0);
}

void server::output(int socket_con, char *header, char *data) {
  /* Send header and data to client */
  send(socket_con, header, strlen(header), 0);
  send(socket_con, data, strlen(data), 0);
}

void server::end(int socket_con) {
  /* Close communication between client and the server */
  close(socket_con);
}

void server::finish() {
  close(socket_srvr);
}
