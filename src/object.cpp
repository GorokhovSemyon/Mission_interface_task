//
// Created by sam on 15.12.22.
//

#include "../hdrs/object.h"
#include <iostream>
#include <string>

object::object(double X, double Y, double Z = 0, double D = 0) {
  x = X;
  y = Y;
  z = Z;
  depth = D;
}

bool object::update_coords(char command, double op1, double op2) {
  std::string result = "none";

  switch (command) {

  case 'M':
    if (op1 < 0 || op2 < 0 || op1 > MAX_X || op2 > MAX_Y) {
      std::cout << "\t Error: "
           << "op1 < 0 or op2 < 0 or op1 > MAX_X or op2 > MAX_Y" << std::endl;
      return false;
    }

    x = op1;
    y = op2;
    break;

  case 'R':
    x = 0;
    y = 0;
    z = 0;
    break;

  case 'D':
    if (op1 > MAX_Z || op1 < 0 || z >= op1) {
      std::cout << "\t Error: "
           << "op1 > MAX_Z or op1 < 0 or z >= op1" << std::endl;
      return false;
    }
    z = op1;
    depth = op1;
    break;

  case 'L':
    if (op1 > MAX_Z || op1 < 0 || z <= op1) {
      std::cout << "\t Error: "
           << "op1 > MAX_Z or op1 < 0 or z <= op1" << std::endl;
      return false;
    }
    z = op1;
    depth = op1;
    break;

  default:
    break;
  }
  return true;
}