#include "uri.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#define MAX_BUF 200

void uri::parse(char *request) {
  int i, j, k, space, pstart;
  char *uri;
  method = new char[4];

  /* Look for the verbs -- first; space/?-delimit */

  for(i=0;i<strlen(request);i++) {
    if(*(request+i)=='/') {
      for(j=i;j<strlen(request);j++) {
        if(*(request+j)==' ') {    
          uri = new char[(j-i-1)];
          for(k=0;k<(j-i);k++) {
            *(uri+k) = *(request+k+i+1);
          }
          i = strlen(request);
          j = strlen(request);
        }
      }
    }
  }

  //std::cout << request << std::endl;
  std::cout << uri << std::endl;

  /* POST method? */
  if((*(request)=='P'||*(request)=='p')) {
    sprintf(method, "POST");
  } 
  else {
    sprintf(method, "GET");
  }

  delete [] uri;
}

uri::~uri() {
  //delete [] controller;
  //delete [] action;
  delete [] method;
}
