#ifndef AUTONOMOUS
#define AUTONOMOUS

#include "dead.h"
#include "red_left.h"
#include "red_right.h"
#include "blue_left.h"
#include "blue_right.h"
#include "skills.h"

namespace autos {

    enum class select {
        red_left = 1,
        red_right = 2,        
        blue_left = 3,
        blue_right = 4,
        dead = 5,
        skills = 6
    };

}

#endif