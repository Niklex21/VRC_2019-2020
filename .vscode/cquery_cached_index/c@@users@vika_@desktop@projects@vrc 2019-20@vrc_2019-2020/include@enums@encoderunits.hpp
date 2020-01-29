#ifndef _ENCODER_UNITS_ENUM_
#define _ENCODER_UNITS_ENUM_

#include "main.h"

enum class EncoderUnits {
  degrees = pros::motor_encoder_units_e_t::E_MOTOR_ENCODER_DEGREES,
  rotations = pros::motor_encoder_units_e_t::E_MOTOR_ENCODER_ROTATIONS,
  counts = pros::motor_encoder_units_e_t::E_MOTOR_ENCODER_COUNTS
};

#endif
