#ifndef _GEARSET_ENUM_
#define _GEARSET_ENUM_

#include "main.h"

enum class Gearset {
  red_36 = pros::motor_gearset_e_t::E_MOTOR_GEARSET_36,
  green_18 = pros::motor_gearset_e_t::E_MOTOR_GEARSET_18,
  blue_06 = pros::motor_gearset_e_t::E_MOTOR_GEARSET_06
};

#endif
