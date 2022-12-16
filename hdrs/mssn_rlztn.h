//
// Created by sam on 12.12.22.
//

#ifndef MISSION_H
#define MISSION_H

#include <string>
#include <vector>

using namespace std;

class Mission {
public:
  virtual string toFile() = 0;
};

class MoveTo : public Mission {
public:
  double x = 0;
  double y = 0;

  MoveTo(double X, double Y);
  string toFile() override;
};

class Dive : public Mission {
public:
  double z = 0;

  explicit Dive(double d);
  string toFile() override;
};

class Lift : public Mission {
public:
  double z = 0;

  explicit Lift(double UP);
  string toFile() override;
};

class Return : public Mission {
public:
  Return()= default;
  string toFile() override;
};

#endif // MISSION_H
