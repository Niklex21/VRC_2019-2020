#include "main.h"

#include "enums/TeamColor.hpp"
#include "extended_pros/extended_pros.hpp"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  int teamColor = 1; // 1 for red, -1 for blue
  extended_pros::Robot robot = extended_pros::Robot();

  robot.arm.up();
  pros::delay(1000);
  robot.arm.down();
  robot.arm.intake();

  pros::delay(1000);

  robot.driveChain.moveByTiles(1.5);
  pros::delay(2000);
  robot.driveChain.moveByTiles(-1.5);
  pros::delay(2000);

  robot.driveChain.rotate(-100);
  pros::delay(1000);
  robot.driveChain.moveByTiles(1.2);

  pros::delay(2000);

  robot.stacker.stack();
  pros::delay(3000);
  robot.driveChain.moveByTiles(-1);
  pros::delay(2000);
  robot.stacker.retract();

}
