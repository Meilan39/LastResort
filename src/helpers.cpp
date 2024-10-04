#include "vex.h"

using namespace vex;

/* @brief return the most efficient direction to get from the current to desired angle
* @param current the current angle in degrees (0 ~ 360)
* @param desired the desired angle in degrees (0 ~ 360)
* @return the angles to turn (-180 ~ 180)
*/
double wrap(double current, double desired) {
    double error = current - desired;
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    return -error;
}
/* @brief take any angle and convert it so it is 0 to 360
* @param angle angle to convert in degrees
* @return the angle bounded to the range (0 ~ 360)
*/
double bound(double angle) {
    return fmod( fmod(angle, 360) + 360, 360 );
}
/* @brief if value is in range, return value, if not return min or max
* @param value to fit to range (0 ~ 360)
* @param min of the range (0 ~ 360)
* @param max of the range (0 ~ 360)
* @return value fit to range (min ~ max)
*/
double fitToRange(double value, double min, double max) {
    if (value > max) return max;
    if (value < min) return min;
    return value;
}
/* @brief checks whether value is within setpoint (+ or -) threshold
* @param value     value to check
* @param setpoint  setpoint around which to expand threshold
* @param threshold threshold around the setpoint to consider range
* @return whether the value is in range of the setpoint threshold
*/
bool inRange(double value, double setpoint, double threshold) {
    return (setpoint - threshold < value) && (value < setpoint + threshold);
}  





/* @brief initialize the drive base in pre-auton */
void Drive::init() {
    // begin calibrating the inertial sensor
    Inertial.calibrate();
    // set the stopping mode of the drive motors to brake mode
    FR.setStopping(brake);
    FL.setStopping(brake);
    MR.setStopping(brake);
    ML.setStopping(brake);    
    RR.setStopping(brake);
    RL.setStopping(brake);
    // wait for the inertial sensor to stop calibrating
    while(Inertial.isCalibrating()) {wait(100, msec);}
}
/* @brief stop the drive */
void Drive::stop() {
    FR.stop(); FL.stop(); MR.stop(); ML.stop(); RR.stop(); RL.stop();
}
/* @brief arcade drive for teleop 
 * @param y (-1 backward ~ 1 forward)
 * @param x (-1 left ~ 1 right)
 */
void Drive::drive(double y, double w) {
    double right = y + w;
    double left  = y - w;
    double max   = fmax( fmax( fabs(right), 1 ), left ); // max between 1, abs(right), abs(left)
    right = right/max * MAX_RPM;
    left = left/max * MAX_RPM;
    FR.spin(forward, right, rpm);
    FL.spin(forward, left , rpm);
    RR.spin(forward, right, rpm);
    RL.spin(forward, left , rpm); 
    MR.spin(forward, right, rpm);
    ML.spin(forward, left , rpm); 
}
/* @brief move the drive base forward or backward by "position" at "speed" 
 * @param position position in centimeters to move the drive
 * @param speed speed in percent output (0 ~ 1)
 * @return boolean for if the drive is moving or not
 */
void Drive::moveTo(double position, double speed, int timeout) {
    int timeStamp = timer::system();
    position /= Drive::CIRCUMFERENCE;
    speed *= Drive::MAX_RPM;  
    FR.spinFor(position, rev, speed, rpm, false);
    FL.spinFor(position, rev, speed, rpm, false);
    MR.spinFor(position, rev, speed, rpm, false);
    ML.spinFor(position, rev, speed, rpm, false);    
    RR.spinFor(position, rev, speed, rpm, false);
    RL.spinFor(position, rev, speed, rpm, false);
    do{
        if(timeout && timer::system() - timeStamp > timeout) {}
        wait(10, msec);
    } while(FR.isSpinning()||FL.isSpinning()||
            MR.isSpinning()||ML.isSpinning()||
            RR.isSpinning()||RL.isSpinning());
}
/* @brief rotate the drive base to "angle" 
 * @param angle angle in degrees to rotate the drive motors to
 * @return boolean for if the drive is rotating or not
 */
void Drive::rotateTo(double angle, int timeout) {
    int durationW = 0;
    while ( durationW < 4 ) {
        double error = wrap(Inertial.heading(deg), angle);
        double PID = fitToRange(error * Drive::kp + Drive::kf, -1, 1);
        if (fabs(error) < 1) durationW++;
        Drive::drive( 0, PID );
        wait(10, msec);    
    } Drive::stop();
}





/* initialize the intake */
void Intake::init() {
    intake.setStopping(brake);
    conveyor.setStopping(brake);
    clamp.close();
}
/* stop the intake */
void Intake::stop() {
    intake.stop();
    conveyor.stop();
}
/* run the intake inwards */
void Intake::in() {
    intake.spin(forward, 100, pct);
    conveyor.spin(forward, 100, pct);
}
/* run the intake outwards */
void Intake::out() {
    intake.spin(reverse, 100, pct);
    conveyor.spin(reverse, 100, pct);
}



