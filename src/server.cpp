/*
 (c) 2011, Omar

 */

#include "server.h"
#include "uri.h"
#include "response.h"
#include <iostream>
#include <cstdio>
#include <string>
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
   * In this loop:
   * Parse the request URI -> load controller/action (or defaults)
   * Write to the socket ->  client gets their response
   *
   */
  int socket_con;
  socklen_t length;

  /* Start accepting requests */
  static struct sockaddr_in client_addr;

  length = sizeof(client_addr);
  std::cout << "Waiting..." << std::endl;
  socket_con = accept(socket_srvr, (struct sockaddr *)&client_addr, &length);
  std::cout << "Return value: " << socket_con << std::endl;
  std::cout << "Accepting client info..." << std::endl;
  return socket_con;
}

void server::app(int socket_con) {
  char request[MAX_BUFFER];
  uri *u;
  response *r;
  long read_client;

  std::cout << "Reading request..." << std::endl;
  read_client = recv(socket_con, request, MAX_BUFFER, 0);
  std::cout << "Raw:\n" << request << std::endl;

  /* Interpret the request and create a response here */
  u->parse(request);
  std::cout << "Client request:" << std::endl;
  std::cout << "\tBytes: " << read_client << std::endl;
  std::cout << "\tURL: " << u->url << std::endl;
  std::cout << "\tController: " << u->controller << std::endl;
  std::cout << "\tAction: " << u->action << std::endl;
  r->load(u->url, u->controller, u->action);

  send(socket_con, r->header, strlen(r->header), 0);
  send(socket_con, r->html, strlen(r->html), 0);

  /* Close the connection between the server and the client */
  std::cout << "Closing connection to client..." << std::endl;
  close(socket_con);
  delete u;
  delete r;
  std::cout << "Closed." << std::endl;
}

void server::stop() {
  close(socket_srvr);
}
