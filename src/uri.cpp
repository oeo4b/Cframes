#include "uri.h"
#include <iostream>
#include <cstring>
#include <cstdio>

void uri::parse(char *request) {
  /* Parse the whole request into just the method and URL */
  int i, j;
 
  for(i=0,j=i;request[i]!=' ';i++) {}
  sprintf(method, "%.*s", i, request+j);  

  i++;j=i;
  while((request[i]!=' ')&&(request[i]!='?')) { i++;}
  sprintf(url, "%.*s", i-j, request+j);

  /* Parameters? */
  if((request[i]=='?')&&(request[i+1]!=' ')) { 
    i++;j=i;
    while(request[i]!=' ') { i++; }
    sprintf(parameters, "%.*s", i-j, request+j);
  } else { sprintf(parameters, NULL); } /* Load none */

  /* Now figure out the controller/action from the URL */
  getController();
  getAction();
  getParameters();
}

void uri::getController(void) {
  /* Get controller verb or load default */
  int i, j;
  
  if((strlen(url)>1)&&(url[1]!='/')) {
    for(i=1,j=i;url[i]!='/';i++) {}
    sprintf(controller, "%.*s", i-j, url+j);
  } else { sprintf(controller, "index"); /* load default */ }

}

void uri::getAction(void) {
  /* Get the action verb or load default */
  int i, j;
  bool k = false;

  for(i=1;i<strlen(url);i++) { 
    if(url[i]=='/') { j=i+1; k=true; break;}
  }
  if(k) { sprintf(action, "%.*s", (int)strlen(url)-j, url+j); }
  else { sprintf(action, "index"); /* load default */ }

}

void uri::getParameters() {


}

uri::~uri(void) {

}
