#include <cstdio>
#include "response.h"

bool response::load(char *controller, char *action) {
  header = new char[8096];
  html = new char[8096];

  sprintf(header, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", "text/html");
  sprintf(html, "<html><head></head><body>Hey now</body></html>");
  return true;
}

response::~response(void) {
  delete [] header;
  delete [] html;
}