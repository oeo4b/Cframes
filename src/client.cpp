/*
 (c) 2011, Omar

 */

#include "client.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER 10000

client::client(int socket_srvr) {
  /* 
   * Wait for a client...
   */
  socklen_t length;
  static struct sockaddr_in client_addr;

  length = sizeof(client_addr);
  socket_con = accept(socket_srvr, (struct sockaddr *)&client_addr, &length);
}

void client::input(char *request) {
  /* What does the client want? */
  long read_client;
  read_client = recv(socket_con, request, MAX_BUFFER, 0);
}

void client::output(char *header, bool bin, char *ascii, FILE *fp) {
  long size;
  static char buffer[MAX_BUFFER+1];
  /* Send header and data to client */
  send(socket_con, header, strlen(header), 0);
  
  if(!bin) {
    send(socket_con, ascii, strlen(ascii), 0);
  } else {
    fread(buffer, MAX_BUFFER, 1, fp);
    send(socket_con, buffer, MAX_BUFFER, 0);
  }

}

client::~client() {
  /* Close communication between client and the server */
  close(socket_con);
}
