#include "uri.h"
#include "config/routes.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#define MAX_BUF 200

void uri::parse(char *request) {
  int i, j;
  int start = -1;
  int stop = -1;
  method = new char[4];

  /* Look for the verbs -- first; space/?-delimit */
  for(i=0;i<strlen(request);i++) {
    if((request[i]==' '||request[i]=='?')&&start>0) {
      stop = i;
      i = strlen(request);
    }
    if(request[i]==' '&&start<0) {
      start = i;
    }
  }

  url = new char[(stop-start)-1];
  for(i=(start+1),j=0;i<stop;i++,j++) {
    url[j] = request[i]; 
  }
 
  /* Figure out the verbs from the URI */
  getController();
  getAction();

  /* Params? */
  if(request[stop]=='?') {
    /*
    start = stop+1;
    for(i=start;i<strlen(request);i++) {
      if(request[i]==' ') {
        stop = i;
        i = strlen(request);
      }
    }
    
    parameters = new char[(stop-start)-1];
    for(i=start,j=0;i<stop;i++,j++) {
      par[j] = request[i];
    }

    getParameters();
    */
  }

  /* POST method? */
  if((*(request)=='P'||*(request)=='p')) {
    sprintf(method, "POST");
  } 
  else {
    sprintf(method, "GET");
  }

}

void uri::getAction(void) {
  /* Figure out the action or load a default route */
  int i, j;
  int start = -1;
  int stop = -1;

  /* Delimit by backslash */
  for(i=1;i<strlen(url);i++) {
    if(url[i]=='/') {
      start = i;
      i = strlen(url);
    }
  }

  if(start>0&&(start!=(strlen(url)-1))) {
    stop = strlen(url);
    action = new char[(stop-start)];
    for(i=(start+1),j=0;i<stop;i++,j++) {
      action[j] = url[i];
    }
  }
  else {
    /* From routes */
    action = new char[5];
    sprintf(action, "index");
  }
}

void uri::getController(void) {
  /* Figure out the controller or load the default route */
  int i, j;
  int start = -1;
  int stop = -1;

  /* Isolate the verb */
  for(i=1;i<strlen(url);i++) {
    if(url[i]=='/') {
      stop = i;
      i = strlen(url);
    }
  }

  if(stop==-1&&strlen(url)>1) {
    controller = new char[strlen(url)-1];
    for(i=1,j=0;i<strlen(url);i++,j++) {
      controller[j] = url[i];
    }
  }
  else if(stop==-1) {
    /* Load default from routes */
    controller = new char[5];
    sprintf(controller, "index");
  }
  else {
    controller = new char[(stop-1)];
    for(i=1,j=0;i<stop;i++,j++) {
      controller[j] = url[i];
    }
  }
}

void uri::getParameters() {

}

uri::~uri(void) {
  delete [] controller;
  delete [] action;
  delete [] method;
}
