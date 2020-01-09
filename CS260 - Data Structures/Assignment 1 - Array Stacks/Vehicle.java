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
	int Cylinders;
	int OdomenterMax;
	int length;
	int Width;
	int Height;
	boolean Convertable;
	boolean FourWheelDrive;
	boolean canAccelerate;
	boolean isAccelerating;
	boolean canRoll;
	boolean isRolling;
	boolean canStart;
	boolean vehicleIsOn;
	//Behaviors
		//Base Features of Vehicle
	public Vehicle(){

		Wheels = 4;
		Doors = 2;
		Cylinders = 8;
		OdomenterMax = 180;
		length = 8;
		Width = 6;
		Height = 6;
		Convertable = true;
		FourWheelDrive = true;
		canRoll = true;
		isRolling = false;
		canStart = true;
		vehicleIsOn = false;
	}
		//Roll
			// this will toggle rolling on and off, only if the vehicle is capable of rolling
	public void toggleRoll(){
	if (canRoll == true && isRolling == false){
			isRolling = true;
		}
	else if (canRoll == true && isRolling == true){
			isRolling = false;
		}
	}

		//getter for rolling status
		public boolean getRolling(){
			return isRolling;
		}
		//ToggleOn
			//toggles On state of vehicle
				//addendum, after implementing this I had a revelation that vehicles can roll while not on, so I had modified accordingly.
	public void toggleOn(){
		if (canStart == true && vehicleIsOn == false){
				vehicleIsOn = true;
			}
		else if (canStart == true && vehicleIsOn == true){
				vehicleIsOn = false;
			}
		}

		//getter for on status
		public boolean getOn(){
			return vehicleIsOn;
		}
		//getter for a boolean value that doesnt have a function to modify it
		public boolean isConvertable (){
			return Convertable;
		}
		//getter for an int value that doesnt have a function to modify it.
		public int numWheels (){
			return Wheels;
		}


}



