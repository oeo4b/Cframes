#include <iostream>
#include <cstdio>
#include "response.h"
#include "mvc/controller.h"

bool response::load(char *url, char *controller, char *action) {
  long size;
  char verbp[100];
  char mediap[100];
 
  /* Content pathways */
  sprintf(verbp, "app/views/layouts/%s.html.c", controller);
  sprintf(mediap, "public/%s", url);

  /* Priority: controller, public_html, error */
  if(fp = fopen(verbp,"r")) { status(200, (char *)"text/html"); render(); text(); } 
  else if(fp = fopen(mediap,"rb")) { status(200, (char *)"image/jpeg"); binary(); } 
  else { fp = fopen("public/404.html", "r"); status(404, (char *)"text/html"); text(); }

  return true;
}

void response::binary(void) {
  bin = true;
  ascii = new char[10];
}

void response::render(void) {
  //bin = false;
}

void response::text(void) {
  long size;
  bin = false;

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
  delete [] ascii;
  delete [] header;
}
