#include "main.h"

#include "enums/Controls.hpp"
#include "extended_pros/extended_pros.hpp"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	extended_pros::ExtendedController master(pros::E_CONTROLLER_MASTER);
	extended_pros::Robot robot = extended_pros::Robot();

	while (master.is_connected()) {
		robot.handleControls(master.getPressedDigital(),
												 master.getAnalog());
	}
}
