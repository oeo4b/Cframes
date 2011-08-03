#include <iostream>
#include <cstdio>
#include <cstring>
#include "response.h"
#include "mvc/view.h"
#include "extensions.h"

bool response::load(char *url, char *controller, char *action) {
  long size;
  char verbp[100];
  char mediap[100];
 
  /* Content pathways */
  sprintf(verbp, "app/views/layouts/%s.html.c", controller);
  sprintf(mediap, "public/%s", url);

  /* Priority: controller, public_html, error */
  if(fp = fopen(verbp, "r")) {
    bin = false; 
    status(200, (char *)"text/html"); 
    text(); 
    render(controller, action); 
  } 
  else if(fp = fopen(mediap, "r")) {  
    if(isbin(url)) { 
      fclose(fp); 
      fp = fopen(mediap, "rb"); 
    }
    else { 
      text(); 
    }
  } 
  else {
    bin = false;
    error(404);
    text();
  }

  return true;
}

bool response::isbin(char *url) {
  int i, len;
  bool check = false;

  /* Find the extension and type of URL */
  for(i=0;extensions[i].type!=0;i++) {
    len = strlen(extensions[i].type);

    if(!strncmp(url+strlen(url)-len, extensions[i].type, len)) {
      status(200, extensions[i].http);
      bin = extensions[i].bin;

     /* Binary mode? */
      if(bin) { return true; }
      else { return false; }
    }
  }

  /* For NULL bin -> binary mode by default */
  error(404);
  bin = true; 
  return true;
}

void response::error(int code) {
  fp = fopen("public/404.html", "r"); 
  status(code, (char *)"text/html"); 
}

void response::render(char *controller, char *action) {
  /* Render from controller base class */
  view v(controller, action);
  char copy[strlen(ascii)];

  /* Make a tmp copy of the pre-rendered block and delete */
  strcpy(copy, ascii);
  delete [] ascii;

  /* Send the copy to the render method */
  v.render(copy);
 
  /* Copy the rendered text into the new allocated block */
  ascii = new char[strlen(v.ascii)];
  strcpy(ascii, v.ascii);
}

void response::text(void) {
  /* This method is used to read the file into a memory block */
  long size;

  /* Find the size */
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  /* Read to block */
  ascii =  new char[size];
  fread(ascii, size, 1, fp);
}

void response::status(int code, char *ftype) {
  header = new char[8096];
  sprintf(header, "HTTP/1.0 %d OK\r\nContent-Type: %s\r\n\r\n", code, ftype);
}

response::~response(void) {
  if(fp!=NULL) { fclose(fp); }
  if(!bin) { delete [] ascii; }
  delete [] header;
}
