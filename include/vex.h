#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

extern vex::brain Brain;
extern vex::controller master;
extern vex::motor FR;
extern vex::motor FL;
extern vex::motor MR;
extern vex::motor ML;
extern vex::motor RR;
extern vex::motor RL;
extern vex::motor intake;
extern vex::motor conveyor;
extern vex::inertial Inertial;
extern vex::pneumatics clamp;
extern vex::potV2 potv2;


#ifndef HELPERS
#define HELPERS

/* helper functions */
double wrap(double current, double desired);
double bound(double angle);
double fitToRange(double value, double min, double max);
bool inRange(double value, double setpoint, double threshold);
/* drive base */
namespace Drive {
  constexpr double MAX_RPM = 200;
  constexpr double CIRCUMFERENCE = 31.919;
  constexpr double kp = 0.008;
  constexpr double kf = 0.008;
  void init();
  void stop();
  void drive(double y, double w);
  void moveTo(double position, double speed, int timeout = 0);
  void rotateTo(double angle, int timeout = 0);
}
/* intake */
namespace Intake {
  void init();
  void stop();
  void in();
  void out();
}

#endif

