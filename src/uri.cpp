#include "uri.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#define MAX_BUF 200

void uri::parse(char *request) {
  int i, j;

  method = new char[MAX_BUF];
  for(i=0,j=0;request[i]!=' ';i++,j++) {
    method[j] = request[i];
  }
  std::cout << i << std::endl;

  url = new char[MAX_BUF];
  /*for(i++,j=0;request[i]!=' ';i++,j++) {
    url[j] = request[i];
    }*/

  sprintf(url, "url");

  std::cout << i << std::endl;

  action = new char[MAX_BUF];
  controller = new char[MAX_BUF];

  sprintf(action, "blank");
  sprintf(controller, "blank");
}

void uri::getAction(void) {
}

void uri::getController(void) {
}

void uri::getParameters() {

}

uri::~uri(void) {
  delete [] controller;
  delete [] action;
  delete [] method;
  delete [] url;
}
