#ifndef _EXTENDER_CONTROLLER_
#define _EXTENDER_CONTROLLER_

#include "main.h"

#include "enums/controls.hpp"
#include "enums/gearset.hpp"
#include "enums/encoder_units.hpp"

#include <vector>

namespace extended_pros {
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
    ExtendedMotor leftBack = ExtendedMotor(1, Gearset::green_18, false,
                                           EncoderUnits::rotations);
    ExtendedMotor rightBack = ExtendedMotor(2, Gearset::green_18, true,
                                          EncoderUnits::rotations);
    ExtendedMotor leftFront = ExtendedMotor(3, Gearset::green_18, false,
                                           EncoderUnits::rotations);
    ExtendedMotor rightFront = ExtendedMotor(4, Gearset::green_18, true,
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
    // Setter methods
  private:
    DriveChain driveChain = DriveChain();
};
}

#endif
