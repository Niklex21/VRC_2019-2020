#include "main.h"

#include "extended_pros/extended_pros.hpp"

using namespace extended_pros;

// --------- extended_pros::ExtendedMotor::functions ------------ //
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

// --------- extended_pros::Stacker::functions ------ //
void Stacker::stack(){
  // TODO Stack code using sensors
  this->stackerCond = StackerCondition::stacking;
  this->stackerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->stackerMotor.move_absolute(80, 5);
}

void Stacker::retract(){
  // TODO Retract code using sensors
  this->stackerCond = StackerCondition::retracted;
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

// --------- extended_pros::Arm::functions ---------- //
void Arm::up(){
  // Code for up
  this->armMotor.move_velocity(100);
}

void Arm::down(){
  // Code for down
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

void Arm::armStop(){
  this->armMotor.move(0);
  this->armMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void Arm::intakeStop(){
  this->intakeMotorLeft.move(0);
  this->intakeMotorRight.move(0);
}

// --------- extended_pros::Robot::functions -------- //
void Robot::handleControls(std::vector<DigitalControls> digitalControls,
                           Analog joysticks){
  this->tankControls(joysticks.left.y, joysticks.right.y);

  // R2 is for arm-up, L2 is for arm-down
  // Both are hold
  if (isInVector(digitalControls, DigitalControls::r1)){
    this->arm.up();
  }
  else if (isInVector(digitalControls, DigitalControls::l1)){
    this->arm.down();
  }
  else {
    this->arm.armStop();
  }

  // R1 is for intake, L1 is for "outtake"
  // Both are hold
  if (isInVector(digitalControls, DigitalControls::r2)){
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
}

void Robot::tankControls(int leftJoystickY, int rightJoystickY){
  this->driveChain.moveLeftSide(leftJoystickY);
  this->driveChain.moveRightSide(rightJoystickY);
}
