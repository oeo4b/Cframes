#include "script.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

string script::R(string controller, string action) {
  /* Main method to call R scripts */
  string rendered;
  string randomstr = makerandomstr(10);
  string filepath = "tmp/rendered."+randomstr+".out";
  string call = "R --slave -f R/main.R --args "+controller+" "+action+" > "+filepath;

  /* Subprocess */
  int check;
  check = system(call.c_str());

  /* Not implemented yet -- Rendered file to string */
  int length;
  ifstream renderedfile;
  renderedfile.open(filepath.c_str());

  /* A tmp file is read into the program -- eventually want to stdin */
  renderedfile.seekg(0, ios::end);
  length = renderedfile.tellg();
  renderedfile.seekg(0, ios::beg);

  char *buffer = new char[length];

  renderedfile.read(buffer, length);
  renderedfile.close();

  int i;
  for(i=0;i<length;i++) {
    rendered += buffer[i];
  }

  /* Flush tmp file and return */
  call = "rm "+filepath;
  check = system(call.c_str());
  return rendered;
}

string script::makerandomstr(int chars) {
  int i;
  string randomized;
  srand(time(NULL));

  for(i=0;i<chars;i++) {
    randomized += (char)(rand()%25+97);
  }
  return randomized;
}
