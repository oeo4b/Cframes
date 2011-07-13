#include "server.h"
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BUFSIZE 8096

server::server (int port) {
  /* Create the socket */
  struct sockaddr_in server_addr;

  socket_srvr = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(port);
  
  bind(socket_srvr, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(socket_srvr, 64);
}

void server::start(char *html) {
  long read_client;
  char buffer[BUFSIZE-1];
  /* Start accepting requests */
  struct sockaddr_in client_addr;

  length = sizeof(client_addr);
  socket_con = accept(socket_srvr, (struct sockaddr *)&client_addr, &length);
  
  read_client = read(socket_con, buffer, BUFSIZE);
  std::cout << buffer << std::endl;

  sprintf(buffer, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", "text/html");
  write(socket_con, buffer, strlen(buffer));

  write(socket_con, html, strlen(html));
  close(socket_con);
}

void server::stop() {
  close(socket_srvr);
}
