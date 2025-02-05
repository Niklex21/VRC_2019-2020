#ifndef _EXTENDER_CONTROLLER_
#define _EXTENDER_CONTROLLER_

#include "main.h"

#include "enums/controls.hpp"

#include <vector>

namespace extended_pros {
class ExtendedController : public pros::Controller {
  public:
  /**
   * An extended method to pros::Controller that returns all
   * controls currently in use.
   *
   *\return an std::vector of Controls enum of all controls currently in use.
   */
  ExtendedController(pros::controller_id_e_t id);

  std::vector<DigitalControls> getPressedDigital(void);
};

class ExtendedMotor : public pros::Motor{
public:
  ExtendedMotor(int port);
};

class Robot {
  public:
    Robot(void);

    void handleControls(std::vector <DigitalControls> digitalControls);
};
}

#endif
