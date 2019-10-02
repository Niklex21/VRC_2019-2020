#ifndef _EXTENDER_CONTROLLER_
#define _EXTENDER_CONTROLLER_

#include "main.h"

#include "enums/controls.hpp"
#include "enums/gearset.hpp"
#include "enums/encoder_units.hpp"

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
  ExtendedMotor(int port, Gearset gearset, bool reversed, EncoderUnits enc_un);
};

class Robot {
  public:
    Robot(void);

    /**
     * A handler function to handle simultaneous press of digital controls
     * @param digitalControls A vector of @type DigitalControls enum, includes
     * all the digital controls that are currently pressed and their states
     * (new_press or on hold)
     */
    void handleControls(std::vector <DigitalControls> digitalControls);
};
}

#endif
