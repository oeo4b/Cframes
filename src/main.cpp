/*
*
* (c) 2011, Omar O
*  
*
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 8096

class HTTPrequest {
  char *buffer;
  char *method;
  char *uri;
  long ret;
  int i, j, space, fd, file_fd;
public:
  HTTPrequest(int);
  ~HTTPrequest();
};

HTTPrequest::HTTPrequest (int f) {
  buffer = new char[BUFSIZE-1];
  fd = f;
  ret = read(fd, buffer, BUFSIZE);
  /* Retrieve the method and URI */
  space = 0;
  for(i=0;i<ret;i++) {
    if(buffer[i]==' ') {
      space++;
      if(space==2) {
        uri = new char [i+1];
        for(j=0;j<i;j++) {
          uri[j] = buffer[j];
        }
        i = ret;
      }
    }
  }
  std::cout << buffer << std::endl;
  delete [] buffer;
  delete [] uri;
}

HTTPrequest::~HTTPrequest() {
  buffer = new char[BUFSIZE-1];
  sprintf(buffer, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", "text/html");
  write(fd, buffer, strlen(buffer));

  //file_fd = open("index.html", O_RDONLY);
  //ret = read(file_fd, buffer, BUFSIZE);

  sprintf(buffer, "<html><head></head><body><p>Hey now</p></body></html>");
  write(fd, buffer, strlen(buffer));
  close(fd);
  delete [] buffer;
}


int main(int argc, char **argv) {
  int i, port, pid, listenfd, socketfd, hit;
  size_t length;
  static struct sockaddr_in cli_addr;
  static struct sockaddr_in serv_addr; 

  /* First create the socket -> then bind the port */
  listenfd = socket(AF_INET, SOCK_STREAM,0);
  port = atoi(argv[1]);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port);

  bind(listenfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr));
  listen(listenfd,64);

  /* Single-threaded forever loop to handle requests -- NOTE: eventually will have a daemon option -d */
  for(hit=1;hit<100;hit++) {
    length = sizeof(cli_addr);
    socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length);
    HTTPrequest req(socketfd);
  }
  close(listenfd);
  return 0;
}

