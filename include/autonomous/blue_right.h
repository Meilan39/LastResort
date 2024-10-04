#ifndef BLUERIGHT
#define BLUERIGHT

    #include "vex.h"

    namespace autos {

        // start between 4th and 5th tile
        void blue_right() {
            // start moving and unclamp
            clamp.open();
            Drive::moveTo(-74.28, 0.8);
            // clamp down on mobile goal
            clamp.close();
            // rotate to blue-red stack (360 - 111)
            Drive::rotateTo(249); 
            // start moving and start intake
            Intake::in();
            Drive::moveTo(64.21, 0.8);
            // turn to face ladder
            Drive::rotateTo(90);
            // move to touch the ladder leg and stop the intake
            Drive::moveTo(110, 0.3, 3000); // timeout after three seconds
            // stop intake
            Intake::stop();
        }

    }

#endif

// 

// 45.72 cm drive base
// 22.86 cm half of drive base
// a tile is 60 cm 
// a tile's diagonal is 84.85
// a tile's diagonal's half is 42.43

// 22.86 |____
//         60

// 60 |_____
//     82.86
// 180 - (arctan(60 / 82.86) * 180 / pi)