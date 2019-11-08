#ifndef _EXTENDER_CONTROLLER_
#define _EXTENDER_CONTROLLER_

#include "main.h"

#include "enums/Controls.hpp"
#include "enums/Gearset.hpp"
#include "enums/EncoderUnits.hpp"
#include "enums/StackerCondition.hpp"

#include <vector>
#include <algorithm>

namespace extended_pros {

const int MAXIMUM_SPEED_UN = 127;

template <typename T>
bool isInVector(std::vector<T>& vec, T elem){
  return std::find(vec.begin(), vec.end(), elem) != vec.end();
}

struct Joystick {
  int x;
  int y;
};

struct Analog {
  Joystick left;
  Joystick right;
};

class ExtendedController : public pros::Controller {
  public:
  /**
   * An extended method to pros::Controller that returns all
   * controls currently in use.
   *
   *\return an std::vector of Controls enum of all controls currently in use.
   */
  ExtendedController(pros::controller_id_e_t id) : pros::Controller(id){};

  std::vector<DigitalControls> getPressedDigital(void);
  Analog getAnalog(void);
};

class ExtendedMotor : public pros::Motor{
  public:
    ExtendedMotor(const std::uint8_t _port, const Gearset _gearset, const bool _reversed,
                  const EncoderUnits _enc_un) :
                    pros::Motor(_port, pros::motor_gearset_e_t(_gearset),
                                _reversed, pros::motor_encoder_units_e_t(_enc_un)){
                                  this->port = _port;
                                  this->gearset = _gearset;
                                  this->reversed = _reversed;
                                  this->encoderUnits = _enc_un;
                                };
    ExtendedMotor& operator = (const ExtendedMotor& second);
  private:
    std::uint8_t port;
    Gearset gearset;
    bool reversed;
    EncoderUnits encoderUnits;
};

class DriveChain {
  public:
    DriveChain(void){};
    DriveChain& operator = (const DriveChain& second);

    void move(int speed);
    void moveLeftSide(int speed);
    void moveRightSide(int speed);
  private:
    ExtendedMotor leftBack = ExtendedMotor(11, Gearset::green_18, false,
                                           EncoderUnits::rotations);
    ExtendedMotor rightBack = ExtendedMotor(20, Gearset::green_18, true,
                                          EncoderUnits::rotations);
    ExtendedMotor leftFront = ExtendedMotor(1, Gearset::green_18, false,
                                           EncoderUnits::rotations);
    ExtendedMotor rightFront = ExtendedMotor(10, Gearset::green_18, true,
                                           EncoderUnits::rotations);
};

class Stacker {
  public:
    Stacker(void){};

    void stack();
    void retract();
    void switchStacker();
  private:
    ExtendedMotor stackerMotor = ExtendedMotor(5, Gearset::red_36, false,
                                              EncoderUnits::degrees);
    StackerCondition stackerCond = StackerCondition::retracted;
};

class Arm {
  public:
    Arm(void){};

    void up();
    void down();

    void intake();
    void outtake();

    void armStop();
    void intakeStop();
  private:
    ExtendedMotor intakeMotorLeft = ExtendedMotor(6, Gearset::green_18, false,
                                              EncoderUnits::rotations);
    ExtendedMotor intakeMotorRight = ExtendedMotor(7, Gearset::green_18, true,
                                              EncoderUnits::rotations);
    ExtendedMotor armMotor = ExtendedMotor(2, Gearset::red_36, false,
                                              EncoderUnits::rotations);
};

class Robot {
  public:
    Robot(void){};

    /**
     * A handler function to handle simultaneous press of digital controls
     * @param digitalControls A vector of @type DigitalControls enum, includes
     * all the digital controls that are currently pressed and their states
     * (new_press or on hold)
     */
    void handleControls(std::vector <DigitalControls> digitalControls,
                        Analog joysticks);
    void tankControls(int leftJoystickY, int rightJoystickY);
  private:
    DriveChain driveChain = DriveChain();
    Stacker stacker = Stacker();
    Arm arm = Arm();
};
}

#endif
