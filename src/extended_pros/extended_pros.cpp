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
  this->leftBack.move_absolute(distance, 80);
  this->leftFront.move_absolute(distance, 80);
}

void DriveChain::moveRightSideAbs(double distance){
  this->rightBack.move_absolute(distance, 80);
  this->rightFront.move_absolute(distance, 80);
}

void DriveChain::moveByTiles(double tiles){
  this->rightBack.tare_position();
  this->leftBack.tare_position();
  this->rightFront.tare_position();
  this->leftFront.tare_position();

  this->moveLeftSideAbs(tiles*TILE_CONSTANT);
  this->moveRightSideAbs(tiles*TILE_CONSTANT);

  pros::delay(1500*std::abs(tiles));
}

void DriveChain::rotate(int degrees){
  this->rightBack.tare_position();
  this->leftBack.tare_position();
  this->rightFront.tare_position();
  this->leftFront.tare_position();

  this->moveLeftSideAbs(-degrees*ROTATION_CONSTANT);
  this->moveRightSideAbs(degrees*ROTATION_CONSTANT);
}

// --------- extended_pros::Stacker::functions ------ //
void Stacker::stack(int speed){
  // TODO Stack code using sensors
  this->stackerCond = StackerCondition::stacking;
  // this->targetPos = this->STACK_POS;
  this->stackerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->stackerMotor.move_absolute(760, speed);
}

void Stacker::moveTo(double position, int speed){
  this->stackerCond = StackerCondition::stacking;
  this->stackerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->stackerMotor.move_absolute(std::max(100.00, std::min(position*760, 380.00)), speed);
}

void Stacker::retract(int speed){
  // TODO Retract code using sensors
  this->stackerCond = StackerCondition::retracted;
  // this->targetPos = this->RETRACT_POS;
  this->stackerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->stackerMotor.move_absolute(0, speed);
}

void Stacker::switchStacker(){
  if (this->stackerCond == StackerCondition::retracted){
    this->stack(50);
  }
  else {
    this->retract(50);
  }
}

void Stacker::enableHold(){
  this->stackerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void Stacker::disableHold(){
  this->stackerMotor.set_brake_mode(MOTOR_BRAKE_COAST);
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
  this->armMotor.move_velocity(-100);
}

void Arm::armStop(){
  this->armMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->armMotor.move_velocity(0);
}

double Arm::getPosition(){
  // Return it in percent
  return this->armMotor.get_position() / 1097;
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

void Intake::intake(int percent){
  // Code for intake
  this->intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->intakeMotorRight.set_brake_mode(MOTOR_BRAKE_HOLD);

  this->intakeMotorLeft.move(MAXIMUM_SPEED_UN*percent/100);
  this->intakeMotorRight.move(MAXIMUM_SPEED_UN*percent/100);
}

void Intake::outtake(int percent){
  // Code for outtake
  this->intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->intakeMotorRight.set_brake_mode(MOTOR_BRAKE_HOLD);

  this->intakeMotorLeft.move(-MAXIMUM_SPEED_UN*percent/100);
  this->intakeMotorRight.move(-MAXIMUM_SPEED_UN*percent/100);
}

void Intake::intakeStop(){
  this->intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->intakeMotorRight.set_brake_mode(MOTOR_BRAKE_HOLD);

  this->intakeMotorLeft.move(0);
  this->intakeMotorRight.move(0);
}

void Intake::stackOuttake(){
  this->intakeMotorLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
  this->intakeMotorRight.set_brake_mode(MOTOR_BRAKE_HOLD);

  this->intakeMotorLeft.move(-10);
  this->intakeMotorRight.move(-10);
}
// --------- extended_pros::Robot::functions -------- //
void Robot::handleControls(std::vector<DigitalControls> digitalControls,
                           Analog joysticks){

  if (joysticks.left.y < 0 && joysticks.right.y < 0 && this->stacker.stackerCond == StackerCondition::stacking){
    this->intake.outtake(20);
  }

  this->tankControls(joysticks.left.y, joysticks.right.y);

  //this->intake.stacking = this->stacker.stackerCond == StackerCondition::stacking;

  //std::cerr << this->stacker.getPotentiometerValue() << "\n";

  // New B press to stack/retract stacker (trigger)
  if (isInVector(digitalControls, DigitalControls::b_np)){
    this->switchStacker();
  }

  if (isInVector(digitalControls, DigitalControls::r1)){
    this->armUp();
  }
  else if (isInVector(digitalControls, DigitalControls::r2)){
    this->armDown();
  }
  else {
    this->armStop();
  }

  if (isInVector(digitalControls, DigitalControls::l1)){
    this->intake.intake(95);
  }
  else if  (isInVector(digitalControls, DigitalControls::l2)){
    this->intake.outtake(60);
  }
  else{
    this->intake.intakeStop();
  }

  if (isInVector(digitalControls, DigitalControls::right_np) &&
      isInVector(digitalControls, DigitalControls::down_np)){
    this->unfold();
  }

  // For Debug
  // if (isInVector(digitalControls, DigitalControls::left_np) &&
  //     isInVector(digitalControls, DigitalControls::up_np)){
  //   autonomous();
  // }
}

void Robot::tankControls(int leftJoystickY, int rightJoystickY){
  this->driveChain.moveLeftSide(leftJoystickY);
  this->driveChain.moveRightSide(rightJoystickY);
}

void Robot::unfold(){
  this->stacker.stack(200);
  this->intake.outtake(100);
  pros::delay(1200);
  this->stacker.retract(60);
  pros::delay(1000);
  this->intake.intakeStop();
}

void Robot::stack(){
  // this->intake.outtake(30);
  this->stacking = true;
  this->intake.outtake(10);
  this->stacker.stack(60);
  pros::delay(2500);
  // this->driveChain.moveByTile
}

void Robot::retract(){
  this->intake.intake(30);
  this->retracting = true;
  this->stacker.retract(60);
}

void Robot::switchStacker(){
  if (this->stacker.stackerCond == StackerCondition::stacking){
    this->retract();
  }
  else {
    this->stack();
  }
}

void Robot::armUp(){
  this->stacker.disableHold();
  this->arm.up();
}

void Robot::armDown(){
  this->stacker.disableHold();
  this->arm.down();
}

void Robot::armStop(){
  this->arm.armStop();
  this->stacker.enableHold();
}

void Robot::defaultState(){
  this->armDown();
  this->intake.intakeStop();
}
