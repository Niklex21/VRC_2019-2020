#include "main.h"

#include "extended_pros/extended_pros.hpp"

std::vector<DigitalControls> extended_pros::ExtendedController::getPressedDigital(void){
  std::vector <DigitalControls> controlsActive = {};

  if (this->get_digital(DIGITAL_X))
    controlsActive.push_back(DigitalControls::x);
  else if (this->get_digital_new_press(DIGITAL_X))
    controlsActive.push_back(DigitalControls::x_np);
  if (this->get_digital(DIGITAL_Y))
    controlsActive.push_back(DigitalControls::y);
  else if (this->get_digital_new_press(DIGITAL_Y))
    controlsActive.push_back(DigitalControls::y_np);
  if (this->get_digital(DIGITAL_A))
    controlsActive.push_back(DigitalControls::a);
  else if (this->get_digital_new_press(DIGITAL_A))
    controlsActive.push_back(DigitalControls::a_np);
  if (this->get_digital(DIGITAL_B))
    controlsActive.push_back(DigitalControls::b);
  else if (this->get_digital_new_press(DIGITAL_B))
    controlsActive.push_back(DigitalControls::b_np);


  if (this->get_digital(DIGITAL_RIGHT))
    controlsActive.push_back(DigitalControls::right);
  else if (this->get_digital_new_press(DIGITAL_RIGHT))
    controlsActive.push_back(DigitalControls::right_np);
  if (this->get_digital(DIGITAL_DOWN))
    controlsActive.push_back(DigitalControls::down);
  else if (this->get_digital_new_press(DIGITAL_DOWN))
    controlsActive.push_back(DigitalControls::down_np);
  if (this->get_digital(DIGITAL_LEFT))
    controlsActive.push_back(DigitalControls::left);
  else if (this->get_digital_new_press(DIGITAL_LEFT))
    controlsActive.push_back(DigitalControls::left_np);
  if (this->get_digital(DIGITAL_UP))
    controlsActive.push_back(DigitalControls::up);
  else if (this->get_digital_new_press(DIGITAL_UP))
    controlsActive.push_back(DigitalControls::up_np);

  if (this->get_digital(DIGITAL_L1))
    controlsActive.push_back(DigitalControls::l1);
  else if (this->get_digital_new_press(DIGITAL_L1))
    controlsActive.push_back(DigitalControls::l1_np);
  if (this->get_digital(DIGITAL_L2))
    controlsActive.push_back(DigitalControls::l2);
  else if (this->get_digital_new_press(DIGITAL_L2))
    controlsActive.push_back(DigitalControls::l2_np);
  if (this->get_digital(DIGITAL_R1))
    controlsActive.push_back(DigitalControls::r1);
  else if (this->get_digital_new_press(DIGITAL_R1))
    controlsActive.push_back(DigitalControls::r1_np);
  if (this->get_digital(DIGITAL_R2))
    controlsActive.push_back(DigitalControls::r2);
  else if (this->get_digital_new_press(DIGITAL_R2))
    controlsActive.push_back(DigitalControls::r2_np);

  return controlsActive;
}
