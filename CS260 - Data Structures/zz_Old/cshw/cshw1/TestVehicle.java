//Nick Skinner
//Document Driver
//read values/functions from cshw1list, run them(if possible) and print their status.

public class TestVehicle{


	public static void main(String[] args){
		Vehicle myVehicle = new Vehicle();


		myVehicle.toggleRoll();
		myVehicle.toggleOn();
		System.out.println("is my vehicle on? \t" + myVehicle.getOn());
		System.out.println("is vehicle rolling? \t" + myVehicle.getRolling());
		System.out.println("is this a convertable? \t" + myVehicle.isConvertable());
		System.out.println("How many Wheels? \t" + myVehicle.numWheels());



	}
}