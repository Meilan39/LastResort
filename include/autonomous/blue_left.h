#ifndef BLUELEFT
#define BLUELEFT

    #include "vex.h"

    namespace autos {

        // start between 2nd and 3rd tile
        void blue_left() {
            // start moving and unclamp
            clamp.open();
            Drive::moveTo(74.28, 0.8);
            // clamp down on mobile goal
            clamp.close();
            // rotate to blue-red stack
            Drive::rotateTo(111);
            // start moving and start intake
            Intake::in();
            Drive::moveTo(64.21, 0.8);
            // turn to face ladder
            Drive::rotateTo(270);
            // move to touch the ladder leg and stop the intake
            Drive::moveTo(110, 0.3, 3000); // timeout after three seconds
            // stop intake
            Intake::stop();
        }

    }

#endif


