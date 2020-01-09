//
//


import java.util.*;

	public class Arraystack {
   	public static void main(String args[]) {

   	Stack Vehicle= new Stack();
   	String nick;

   	Vehicle.push("Ford");
   	Vehicle.push("Jeep");
  	Vehicle.push("BMW");
	System.out.println("peek at the most recent item: " + Vehicle.peek());
	System.out.println("Most recent, and popped object is: "+Vehicle.pop());
	System.out.println("Objects that remain: "+Vehicle);
	System.out.println("Most recent, and popped object is: "+Vehicle.pop());
	System.out.println("Objects that remain: "+Vehicle);
	System.out.println("Adding a few new objects to the stack.");
	Vehicle.push("Nissan");
	Vehicle.push("Ram");
	Vehicle.push("GMC");
	Vehicle.push("TransAm");
	Vehicle.push("Honda");
	Vehicle.push("Mom's Spaghetti");
	System.out.println("Objects after add: " +Vehicle);
	System.out.println("is this stack empty?: " +Vehicle.empty());

   }
}