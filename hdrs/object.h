//
// Created by sam on 15.12.22.
//

#ifndef ROV_H
#define ROV_H

class object {

public:
  double x = 0;
  double y = 0;
  double z = 0;
  double depth = 0;

  const int MAX_X = 5000;
  const int MAX_Y = 5000;
  const int MAX_Z = 250;
  const int MAX_DEPTH = 123;

  object(double X, double Y, double Z, double D);
  ~object()= default;

  bool update_coords(char command, double op1, double op2 = -1);
};

#endif // ROV_H
