#include "main.h"

#include "extended_pros/ExtendedController.hpp"

using namespace extended_pros;

std::vector<DigitalControls> ExtendedController::getPressedDigital(void){
  std::vector <DigitalControls> controlsActive = {};

  if (this->get_digital_new_press(DIGITAL_X))
    controlsActive.push_back(DigitalControls::x_np);
  else if (this->get_digital(DIGITAL_X))
    controlsActive.push_back(DigitalControls::x);
  if (this->get_digital_new_press(DIGITAL_Y))
    controlsActive.push_back(DigitalControls::y_np);
  else if (this->get_digital(DIGITAL_Y))
    controlsActive.push_back(DigitalControls::y);
  if (this->get_digital_new_press(DIGITAL_A))
    controlsActive.push_back(DigitalControls::a_np);
  else if (this->get_digital(DIGITAL_A))
    controlsActive.push_back(DigitalControls::a);
  if (this->get_digital_new_press(DIGITAL_B))
    controlsActive.push_back(DigitalControls::b_np);
  else if (this->get_digital(DIGITAL_B))
    controlsActive.push_back(DigitalControls::b);

  if (this->get_digital_new_press(DIGITAL_RIGHT))
    controlsActive.push_back(DigitalControls::right_np);
  else if (this->get_digital(DIGITAL_RIGHT))
    controlsActive.push_back(DigitalControls::right);
  if (this->get_digital_new_press(DIGITAL_DOWN))
    controlsActive.push_back(DigitalControls::down_np);
  else if (this->get_digital(DIGITAL_DOWN))
    controlsActive.push_back(DigitalControls::down);
  if (this->get_digital_new_press(DIGITAL_LEFT))
    controlsActive.push_back(DigitalControls::left_np);
  else if (this->get_digital(DIGITAL_LEFT))
    controlsActive.push_back(DigitalControls::left);
  if (this->get_digital_new_press(DIGITAL_UP))
    controlsActive.push_back(DigitalControls::up_np);
  else if (this->get_digital(DIGITAL_UP))
    controlsActive.push_back(DigitalControls::up);

  if (this->get_digital_new_press(DIGITAL_L1))
    controlsActive.push_back(DigitalControls::l1_np);
  else if (this->get_digital(DIGITAL_L1))
    controlsActive.push_back(DigitalControls::l1);
  if (this->get_digital_new_press(DIGITAL_L2))
    controlsActive.push_back(DigitalControls::l2_np);
  else if (this->get_digital(DIGITAL_L2))
    controlsActive.push_back(DigitalControls::l2);
  if (this->get_digital_new_press(DIGITAL_R1))
    controlsActive.push_back(DigitalControls::r1_np);
  else if (this->get_digital(DIGITAL_R1))
    controlsActive.push_back(DigitalControls::r1);
  if (this->get_digital_new_press(DIGITAL_R2))
    controlsActive.push_back(DigitalControls::r2_np);
  else if (this->get_digital(DIGITAL_R2))
    controlsActive.push_back(DigitalControls::r2);

  return controlsActive;
}

Analog ExtendedController::getAnalog(void){
  Analog analogValues;
  analogValues.left = {this->get_analog(ANALOG_LEFT_X),
                       this->get_analog(ANALOG_LEFT_Y)};
  analogValues.right = {this->get_analog(ANALOG_RIGHT_X),
                        this->get_analog(ANALOG_RIGHT_Y)};
  return analogValues;
}
