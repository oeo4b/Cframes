/*
 (c) 2011, Omar

 */

#include "client.h"
#include <iostream>
#include <fstream>
#include <string>
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

void client::output(std::string header, bool bin, std::string ascii, char *media) {
  long size;
  char buffer[MAX_BUFFER+1];

  /* Send header and data to client */
  send(socket_con, header.c_str(), header.length(), 0);
  
  if(!bin) {
    send(socket_con, ascii.c_str(), ascii.length(), 0);
  } else {
    ifstream fp;
    fp.open(media, ios::binary);
    fp.read(buffer, MAX_BUFFER);
    send(socket_con, buffer, MAX_BUFFER, 0);
    fp.close();
  }

}

client::~client() {
  /* Close communication between client and the server */
  close(socket_con);
}
