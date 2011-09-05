#include "script.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

string script::R(string controller, string action) {
  /* Main method to call R scripts */
  string rendered;
  string call = "R --slave -f R/main.R --args "+controller+" "+action+" > tmp/rendered.out";
  int check;
  check = system(call.c_str());

  /* Not implemented yet -- Rendered file to string */
  int length;
  ifstream renderedfile;
  renderedfile.open("tmp/rendered.out");

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
  return rendered;
}
