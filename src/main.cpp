#include "vex.h"
#include "autonomous/autonomous.h"

using namespace vex;

competition Competition;
brain Brain;
controller master;
motor FR {vex::PORT1, ratio18_1, false};
motor FL {vex::PORT2, ratio18_1, true };
motor MR {vex::PORT5, ratio18_1, true };
motor ML {vex::PORT6, ratio18_1, false};
motor RR {vex::PORT3, ratio18_1, false};
motor RL {vex::PORT4, ratio18_1, true };
motor intake {vex::PORT7, ratio18_1, false};
motor conveyor {vex::PORT8, ratio18_1, false};
inertial Inertial {vex::PORT11};
pneumatics clamp {Brain.ThreeWirePort.A};
potV2 potv2 {Brain.ThreeWirePort.B};

autos::select autoSelect;

void pre_auton(void) {
  Drive::init();
  Intake::init();

  while(!Brain.Screen.pressing()) {
    // pot returns (0 ~ 250), four autos so 250/4 = ~60
    autoSelect = (autos::select)(potv2.angle(deg)/60 + 1);
    Brain.Screen.clearScreen(); 
    Brain.Screen.setCursor(1, 3);
    Brain.Screen.print("red left");
    Brain.Screen.setCursor(2, 3);
    Brain.Screen.print("red right");
    Brain.Screen.setCursor(3, 3);
    Brain.Screen.print("blue left");
    Brain.Screen.setCursor(4, 3);
    Brain.Screen.print("blue right");  
    Brain.Screen.setCursor(5, 3);
    Brain.Screen.print("dead");
    Brain.Screen.setCursor(6, 3);
    Brain.Screen.print("skills");    
    Brain.Screen.setCursor((int)autoSelect , 1);
    Brain.Screen.print("~");
    wait(20, msec);    
  } 
  Brain.Screen.setCursor(7, 1);
  Brain.Screen.print("Confirmed");
}

void autonomous(void) {
  // the run the corresponding autonomous
  switch(autoSelect) {
    case autos::select::red_left : autos::red_left(); break;
    case autos::select::red_right : autos::red_right(); break;
    case autos::select::blue_left : autos::blue_left(); break;
    case autos::select::blue_right : autos::blue_right(); break;
    case autos::select::dead : autos::dead(); break;
    case autos::select::skills : autos::skills(); break;
    default : break;
  }
}

void usercontrol(void) {
  while (1) {
    // drive
    Drive::drive(master.Axis3.value()/127, master.Axis1.value()/127);
    // intake
    if      (master.ButtonR1.pressing()) Intake::in();
    else if (master.ButtonR2.pressing()) Intake::out();
    else    Intake::stop();
    // clamp
    if      (master.ButtonL1.pressing()) clamp.open();
    else if (master.ButtonL2.pressing()) clamp.close();
    // sleep
    wait(20, msec); 
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
