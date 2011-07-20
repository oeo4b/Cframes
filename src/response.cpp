#include <iostream>
#include <cstdio>
#include "response.h"
#include "mvc/controller.h"

bool response::load(char *url, char *controller, char *action) {
  long size;
  FILE *verb;
  FILE *media;
  char verbp[100];
  char mediap[100];

  header = new char[8096];
  sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", "text/html");
 
  sprintf(verbp, "app/views/layouts/%s.html.c", controller);
  sprintf(mediap, "public/%s", url);
 
  verb = fopen(verbp,"r");
  media = fopen(mediap, "r");

  if(verb!=NULL) {
    /* Run the controller and load the view */ 
    fseek(verb, 0, SEEK_END);
    size = ftell(verb);
    fseek(verb, 0, SEEK_SET);

    data = new char[size];
    fread(data, size, 1, verb);
  }
  else if(media!=NULL) {
    /* Different media type? */
    fseek(media, 0, SEEK_END);
    size = ftell(media);
    fseek(media, 0, SEEK_SET);

    data = new char[size];
    fread(data, size, 1, media);    
  }
  else {
   data = new char[250];
   sprintf(data, "<html><head></head><body><p>404. That's an error.<br>The requested URL %s was not found on this server.</p></body></html>","/url");
  }

  if(verb!=NULL) { fclose(verb); }
  if(media!=NULL) { fclose(media); }

  return true;
}

response::~response(void) {
  delete [] header;
  delete [] data;
}
