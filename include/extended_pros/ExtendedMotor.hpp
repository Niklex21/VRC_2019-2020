#ifndef _EXTENDED_PROS_MOTOR_HPP_
#define _EXTENDED_PROS_MOTOR_HPP_

#include "main.h"

#include "enums/Gearset.hpp"
#include "enums/EncoderUnits.hpp"

namespace extended_pros {
  class ExtendedMotor : public pros::Motor{
    public:
      ExtendedMotor(const std::uint8_t _port, const Gearset _gearset,
                    const bool _reversed, const EncoderUnits _enc_un) :
                      pros::Motor(_port, pros::motor_gearset_e_t(_gearset),
                                  _reversed,
                                  pros::motor_encoder_units_e_t(_enc_un)){};
      ExtendedMotor& operator = (const ExtendedMotor& second);
    private:
      std::uint8_t port;
      Gearset gearset;
      bool reversed;
      EncoderUnits encoderUnits;
  };
}

#endif
