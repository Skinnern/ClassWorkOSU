//Nicholas Skinner
//3/28/2016
//assignment 1
//Make a list of car properties and behaviors, implement them in a class,
//and test the implementation in a driver class.
//need a seperate drive class

public class Vehicle
{
	//Features
	int Wheels;
	int Doors;
	int Cylanders;
	int OdomenterMax;
	int length;
	int Width;
	int Height;
	boolean Convertable;
	boolean FourWheelDrive;
	boolean haswheels;
	int location;
	int newLocation;
	boolean canAccelerate;
	boolean isAccelerating;
	boolean canRoll;
	boolean isRolling;

	//Behaviors

	//roll

	public Vehicle(){
		canRoll = true;
		isRolling = false;
	}

	public void toggleRoll(){
	// this will toggle rolling on and off, only if the vehicle is capable of rolling
	if (canRoll == true && isRolling == false)
		{
			isRolling = true;
		}
		if (canRoll == true && isRolling == true)
		{
			isRolling = false;
		}
	}

	//public void rollToLocation(int[2] newLocation){
		public void rollToLocation(int[] newLocation){
		if(canRoll){
			location = newLocation;
		}
//error if it cannot roll
		else{
			System.out.print("You are not capable of rolling, please fix your vehicle before driving.\n\n")
		}
}

	//accelerate



	//decelerate

	//position


String[][] Features = {{"Wheels","Doors","Cylanders","Odometer_Max","RPM_Max*1000","Convertable","4_Wheel_Drive","Manufacturer","Warrenty","Used_by_post_office"},{"4","2","4","150","9","No","Yes","JeepyJeep","Yes","Yes"}};
}