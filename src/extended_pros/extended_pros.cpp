#include "main.h"

#include "extended_pros/extended_pros.hpp"

using namespace extended_pros;

// --------- extended_pros::ExtendedController::functions -------------- //
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

// --------- extended_pros::ExtendedMotor::functions ------------ //
ExtendedMotor& ExtendedMotor::operator = (const ExtendedMotor& second){
  this->port = second.port;
  this->gearset = second.gearset;
  this->reversed = second.reversed;
  this->encoderUnits = second.encoderUnits;
  return *this;
}

// --------- extended_pros::DriveChain::functions ---------- //
DriveChain& DriveChain::operator = (const DriveChain& second){
  this->leftBack = second.leftBack;
  this->rightBack = second.rightBack;
  this->leftFront = second.leftFront;
  this->rightFront = second.rightFront;
  return *this;
}

void DriveChain::moveLeftSide(int speed){
  this->leftBack.move(speed);
  this->leftFront.move(speed);
}

void DriveChain::moveRightSide(int speed){
  this->rightBack.move(speed);
  this->rightFront.move(speed);
}

void DriveChain::move(int speed){
  this->moveLeftSide(speed);
  this->moveRightSide(speed);
}

void DriveChain::moveLeftSideAbs(double distance){
  this->leftBack.move_absolute(distance, 200);
  this->leftFront.move_absolute(distance, 200);
}

void DriveChain::moveRightSideAbs(double distance){
  this->rightBack.move_absolute(distance, 200);
  this->rightFront.move_absolute(distance, 200);
}

void DriveChain::moveByTiles(double tiles){
  this->moveLeftSideAbs(tiles*TILE_CONSTANT);
  this->moveRightSideAbs(tiles*TILE_CONSTANT);
}

void DriveChain::rotate(int degrees){
  this->moveLeftSideAbs(-degrees*ROTATION_CONSTANT);
  this->moveRightSideAbs(degrees*ROTATION_CONSTANT);
}

// --------- extended_pros::Stacker::functions ------ //
void Stacker::stack(){
  // TODO Stack code using sensors
  this->stackerCond = StackerCondition::stacking;
  // this->targetPos = this->STACK_POS;
  this->stackerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->stackerMotor.move_absolute(70, 5);
}

void Stacker::retract(){
  // TODO Retract code using sensors
  this->stackerCond = StackerCondition::retracted;
  // this->targetPos = this->RETRACT_POS;
  this->stackerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->stackerMotor.move_absolute(0, 5);
}

void Stacker::switchStacker(){
  if (this->stackerCond == StackerCondition::retracted){
    this->stack();
  }
  else {
    this->retract();
  }
}

void Stacker::update(){
  if (this->potentiometer.get_value() - this->targetPos > 10){
    this->stackerMotor.move_velocity(-5);
  }
  else if (this->potentiometer.get_value() - this->targetPos < -10){
    this->stackerMotor.move_velocity(5);
  }
  else {
    this->stackerMotor.move_velocity(0);
  }
}

int Stacker::getPotentiometerValue(){
  return this->potentiometer.get_value();
}

// --------- extended_pros::Arm::functions ---------- //
void Arm::up(){
  // Code for up
  this->mode = Mode::manual;
  this->armMotor.move_velocity(100);
}

void Arm::down(){
  // Code for down
  this->mode = Mode::manual;
  this->armMotor.move_velocity(-40);
}

void Arm::intake(){
  // Code for intake
  this->intakeMotorLeft.move(MAXIMUM_SPEED_UN);
  this->intakeMotorRight.move(MAXIMUM_SPEED_UN);
}

void Arm::outtake(){
  // Code for outtake
  this->intakeMotorLeft.move(-MAXIMUM_SPEED_UN);
  this->intakeMotorRight.move(-MAXIMUM_SPEED_UN);
}

void Arm::armHold(){
  std::cerr << "ArmHold activated\n";
  this->armMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->armMotor.move(0);
  if (this->mode == Mode::manual){
    this->mode = Mode::automatic;
    this->targetPos = this->armMotor.get_position();
  }
}

void Arm::intakeStop(){
  this->intakeMotorLeft.move(0);
  this->intakeMotorRight.move(0);
}

void Arm::update(){
  if (this->mode == Mode::automatic){
    if (this->armMotor.get_position() - this->targetPos < -7){
      this->armMotor.move_velocity(10);
    }
    else {
      this->armMotor.move_velocity(-5);
    }
  }
}
// --------- extended_pros::Robot::functions -------- //
void Robot::handleControls(std::vector<DigitalControls> digitalControls,
                           Analog joysticks){
  this->tankControls(joysticks.left.y, joysticks.right.y);

  std::cerr << this->stacker.getPotentiometerValue() << "\n";

  // R2 is for arm-up, L2 is for arm-down
  // Both are hold
  if (isInVector(digitalControls, DigitalControls::r1)){
    this->arm.up();
    this->stacker.stack();
  }
  else if (isInVector(digitalControls, DigitalControls::r2)){
    this->arm.down();
    this->stacker.retract(); // Because rubber bands can get off
  }
  else {
    this->arm.armHold();
  }

  if (isInVector(digitalControls, DigitalControls::l1)){
    this->arm.intake();
  }
  else if (isInVector(digitalControls, DigitalControls::l2)){
    this->arm.outtake();
  }
  else {
    this->arm.intakeStop();
  }

  // New B press to stack/retract stacker (trigger)
  if (isInVector(digitalControls, DigitalControls::b_np)){
    this->stacker.switchStacker();
  }

  //this->stacker.update();
  this->arm.update();
}

void Robot::tankControls(int leftJoystickY, int rightJoystickY){
  this->driveChain.moveLeftSide(leftJoystickY);
  this->driveChain.moveRightSide(rightJoystickY);
}
