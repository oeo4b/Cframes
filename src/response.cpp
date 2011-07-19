#include <iostream>
#include <cstdio>
#include "response.h"
#include "mvc/controller.h"

bool response::load(char *url, char *controller, char *action) {
  header = new char[8096];
  //FILE *verb;
  //FILE *media;
  long size;
  //char verbp[100];
  //char mediap[100];

  //sprintf(verbp, "app/views/layouts/%s.html.c", controller);
  //sprintf(mediap, "public/%s", url);

  /*
  verb = fopen(verbp,"r");
  if(verb!=NULL) {
    // Run the controller and load the view 
    fseek(verb, 0, SEEK_END);
    size = ftell(verb);
    fseek(verb, 0, SEEK_SET);

    html = new char[size];
    fread(html, size, 1, verb);
    fclose(verb);
  }
  else if((media=fopen(mediap,"r"))!=NULL) {
    // Different media type? 
    fseek(media, 0, SEEK_END);
    size = ftell(media);
    fseek(media, 0, SEEK_SET);

    html = new char[size];
    fread(html, size, 1, media);    
    fclose(media);
  }
  else {}*/

  html = new char[250];
  sprintf(html, "<html><head></head><body><p>404. That's an error.<br>The requested URL %s was not found on this server.</p></body></html>","/url");
  
  //fclose(verb); 
  sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", "text/html");

  return true;
}

response::~response(void) {
  delete [] header;
  delete [] html;
}
