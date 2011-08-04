#include <iostream>
#include <fstream>
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
  fp.open(verbp);
  if(fp.is_open()) { /* Get verb */
    bin = false; 
    status((char *)"200", (char *)"text/html"); 
    text(); 
    render(controller, action); 
  } 
  else { 
    fp.open(mediap);
    if(fp.is_open()) { /* Get public_html */
      if(isbin(url)) { /* Binary file? */
        strcpy(media, mediap);
      }
      else { /* Text file */
        text();
      }
    }
    else { /* Error */
      bin = false;
      error((char *)"404");
      text();
    }
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
      status((char *)"200", extensions[i].http);
      bin = extensions[i].bin;

     /* Binary mode? */
      if(bin) { return true; }
      else { return false; }
    }
  }

  /* For NULL bin -> binary mode by default */
  error((char *)"404");
  bin = true; 
  return true;
}

void response::error(char *code) {
  fp.open("public/404.html"); 
  status(code, (char *)"text/html"); 
}

void response::render(char *controller, char *action) {
  /* Render from controller base class */
  view v(controller, action);

  /* Return the rendered string */
  ascii = v.render(ascii); 
}

void response::text(void) {
  /* This method is used to read the file into a memory block */
  int size;

  /* Find the size */
  fp.seekg(0, ios::end);
  size = fp.tellg();
  fp.seekg(0, ios::beg);

  /* Read to block */
  /* Major memory leaks here */
  char *buffer = new char[size-1];
  std::cout << "buffer allocated size: " << size << std::endl;
  std::cout << "ascii string length: " << ascii.length() << std::endl;
  fp.read(buffer, size);
  std::cout << "Read buffer: " << strlen(buffer) << std::endl;
  ascii = buffer;
  std::cout << "Ascii block: " << ascii.length() << std::endl;
  delete [] buffer;
}

void response::status(char *code, char *ftype) {
  header = "HTTP/1.0 ";
  header += code;
  header += " OK\r\nContent-Type: ";
  header += ftype;
  header += "\r\n\r\n";
}

response::~response(void) {
  if(fp.is_open()) { fp.close(); }
}
