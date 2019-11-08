#include "main.h"

#include "extended_pros/ExtendedMotor.hpp"

using namespace extended_pros;

ExtendedMotor::ExtendedMotor(const std::uint8_t _port, const Gearset _gearset,
              const bool _reversed, const EncoderUnits _enc_un) :
                pros::Motor(_port, pros::motor_gearset_e_t(_gearset),
                            _reversed,
                            pros::motor_encoder_units_e_t(_enc_un)){
                              this->port = _port;
                              this->gearset = _gearset;
                              this->reversed = _reversed;
                              this->encoderUnits = _enc_un;
                            };

ExtendedMotor& ExtendedMotor::operator = (const ExtendedMotor& second){
  this->port = second.port;
  this->gearset = second.gearset;
  this->reversed = second.reversed;
  this->encoderUnits = second.encoderUnits;
  return *this;
}
