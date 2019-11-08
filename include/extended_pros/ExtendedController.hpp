#ifndef _EXTENDER__PROS_CONTROLLER_HPP_
#define _EXTENDER__PROS_CONTROLLER_HPP_

#include "main.h"

#include "enums/Controls.hpp"
#include "extended_pros/structs.hpp"

namespace extended_pros {
  /*
   *
   */
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
}

#endif
