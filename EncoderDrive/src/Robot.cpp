#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TalonSRX.h>
#include <VictorSP.h>
#include <XboxController.h>
#include <Encoder.h>
#include <Timer.h>
class Robot: public frc::IterativeRobot {
public:

	TalonSRX frontRight{0};
	TalonSRX frontLeft{1};
	VictorSP backRight{2};
	VictorSP backLeft{3};

	XboxController controllerOne{1};

	double driveY;
	double driveX;
	double driveRotate;

	Encoder encoder{1,2};

	static constexpr double waitForUpdate = 0.005;

	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);

		driveY = 0.0;
		driveX =0.0;
		driveRotate = 0.0;


	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {

	}

   	void TeleopPeriodic() {

   	}

	void TestPeriodic() {
		lw->Run();
	}

	void encoderStuffs(){

		encoder.SetSamplesToAverage(5);
		encoder.SetDistancePerPulse(1.0/360.0 * 2.0 * 3.1415 * 2.0);
		encoder.SetMinRate(1.0);

	}

	void encoderFeedBack(){
		while(IsOporatorActive) && (IsEnabled){
			SmartDashboard::PutNumber("Encoder Distance",
								encoder.GetDistance());
			SmartDashboard::PutNumber("Encoder Rate",encoder.GetRate());

			Wait(waitForUpdate);


		}

	}

	void Drive(){

		driveX      = controllerOne.GetRawAxis(4);
		driveY      = controllerOne.GetRawAxis(1);
		driveRotate = controllerOne.GetRawAxis(0);


		frontRight.Set(constrain(driveRotate + driveY + driveX, -1,1));
		frontLeft.Set(constrain(driveRotate - driveY + driveX, -1,1));
        backRight.Set(constrain(driveRotate + driveY - driveX, -1,1));
		backLeft.Set(constrain(driveRotate - driveY  - driveX, -1,1));



	}

	void constrain(double original, double min, double max){

		if(original > max){

			original = max;

		}

		if(original < min){

			original = min;
		}

		return original;
	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
};

START_ROBOT_CLASS(Robot)
