#include "script.h"
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

string script::render(string controller, string action) {
  /* This method yields the rendered action into the controller template */
  string rendered, interpret;
  string::size_type indx = controller.find("<?R");
  string::size_type indy = controller.find("?>");

  /* Check for escape breaks */
  if(indx!=string::npos&&indy!=string::npos) {
    /* Render action */
    action = renderaction(action);
    controller.replace(indx, 2+indy-indx, action);
  }

  return controller;
}
