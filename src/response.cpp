#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "response.h"
#include "script.h"
#include "lib/extensions.h"
#include "lib/http.h"

bool response::load(char *url, char *controller, char *action) {
  long size;
  char controllerp[100];
  char actionp[100];
  char mediap[100];
  bin = false;
 
  /* Content pathways */
  sprintf(controllerp, "app/views/layouts/%s.html.c", controller);
  sprintf(actionp, "app/views/%s/%s.html.c", controller, action);
  sprintf(mediap, "public%s", url);

  /* Priority: controller, public_html, error */
  controllerfp.open(controllerp);
  actionfp.open(actionp);

  if(controllerfp.is_open()&&actionfp.is_open()) { /* Get verb */
    std::cout << "Rendering\t[ " << controller << "/" << action << " ]\n";
    status(200, (char *)"text/html"); 
    render(controller, action);
    
    /* Close the file streams */
    controllerfp.close();
    actionfp.close();
  }
  else {
    /* Close streams if open */
    if(controllerfp.is_open()) controllerfp.close();
    if(actionfp.is_open()) actionfp.close();

    /* Try reading from public dir */
    mediafp.open(mediap);
    if(mediafp.is_open()) { /* Get public_html */
      std::cout << "Reading\t\t[ " << url << " ]\n";
      if(isbin(url)) { /* Binary file? */
        bin = true;
        status(200, getext(url));
        strcpy(media, mediap);
      }
      else { /* Text file */
        status(200, getext(url)); 
        text();
      }
    }
    else { /* Error */
      std::cout << "Bad URL\t\t[ " << url << " ]\n";
      status(404, (char *)"text/html"); 
      mediafp.open("public/404.html");
      text();
    }
    mediafp.close();
  } 

  return true;
}

bool response::isbin(char *url) {
  int i, len;

  /* Binary mode? */
  for(i=0;extensions[i].type!=0;i++) {
    len = strlen(extensions[i].type);
    if(!strncmp(url+strlen(url)-len, extensions[i].type, len)) {
      if(extensions[i].bin) { return true; }
      else { return false; }
    }
  }
  return true;
}

char *response::getext(char *url) {
  int i, len;
  char *dflt = (char *)"text/html"; /* Set the default ext type */

  /* Find the extension and type of URL */
  for(i=0;extensions[i].type!=0;i++) {
    len = strlen(extensions[i].type);
    if(!strncmp(url+strlen(url)-len, extensions[i].type, len)) {
      return extensions[i].http;
    }
  }
  return dflt;
}

void response::render(char *controller, char *action) {
  /* This method is used to read both files into memory and render using the view object */
  int i, csize, asize;
  std::string controllerblock, actionblock;

  /* Find the size */
  controllerfp.seekg(0, ios::end);
  csize = controllerfp.tellg();
  controllerfp.seekg(0, ios::beg);
  
  actionfp.seekg(0, ios::end);
  asize = actionfp.tellg();
  actionfp.seekg(0, ios::beg);

  /* Read to block */
  char *cbuffer = new char[csize];
  char *abuffer = new char[asize];
  controllerfp.read(cbuffer, csize);
  actionfp.read(abuffer, asize);
  for(i=0;i<csize;i++) {
    controllerblock += cbuffer[i];
  }
  for(i=0;i<asize;i++) {
    actionblock += abuffer[i];
  }

  delete [] cbuffer;
  delete [] abuffer;

  /* Create a view object */
  script v;

  /* Return the rendered string via the nested R scripts */
  ascii = v.render(controllerblock, actionblock); 
}

void response::text(void) {
  /* This method is used to read the file into a memory block */
  int i, size;

  /* Find the size */
  mediafp.seekg(0, ios::end);
  size = mediafp.tellg();
  mediafp.seekg(0, ios::beg);

  /* Read to block */
  char *buffer = new char[size];
  mediafp.read(buffer, size);
  for(i=0;i<size;i++) {
    ascii += buffer[i];
  }
  delete [] buffer;
}

void response::status(int code, char *ftype) {
  /* Lookup the header in the http namespace */
  int i;

  header = http::protocol; header += " ";
  for(i=0;http::message[i].lookup!=0;i++) {
    if(http::message[i].lookup==code) {
      /* Send to client and std out */
      header += http::message[i].code; header += " ";
      header += http::message[i].reason; header += " ";
      std::cout << http::message[i].code << " " << http::message[i].reason << "\t";

      /* Content type */
      header += "\r\n";
      header += "Content-Type: ";
      header += ftype;
      header += "\r\n\r\n"; 
    }
  }

}

response::~response(void) {
  /*   */
}
