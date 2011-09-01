#include "view.h"
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

view::view(char *controller, char *action) {
  /* Load the properties from the action */

}

string view::render(string controller, string action) {
  /* This method yields the rendered action into the controller template */
  string rendered, interpret;
  string::size_type indx = controller.find("<?");
  string::size_type indy = controller.find("?>");

  /* Check for escape breaks */
  if(indx!=string::npos&&indy!=string::npos) {
    /* Render action */
    action = renderaction(action);
    controller.replace(indx, 2+indy-indx, action);
  }

  return controller;
}

string view::renderaction(string action) {
  /* Render the loaded properties into the action */
  string render, rendered;
  string::size_type indx, indy, indz;

  /* Check for escape breaks */
  while((indx = action.find("<?"))!=string::npos&&(indy = action.find("?>"))!=string::npos) {
    /* No null space */
    if((indy-indx-2)!=0) {
      render = action.substr(indx+2, indy-indx-2);

      /* Proper usage? */
      indz = render.find_first_not_of(" ");
      if(indz!=string::npos) {
        render = render.substr(indz);

        /* Render action */
        if((render.substr(render.find(" "))).find_first_not_of(" ")!=string::npos) {
          rendered = "hey now";
          action.replace(indx, 2+indy-indx, rendered);

        } else {
          action.erase(indx, 2+indy-indx);
        }

      } else {
        action.erase(indx, 2+indy-indx);
      } 

    } else {
      action.erase(indx, 2+indy-indx);
    }

  }
  
  return action;
}

view::~view(void) {

}
