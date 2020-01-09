import java.util.LinkedList;
import java.util.Scanner;
import java.util.InputMismatchException;


public class LinkedListMethods{
	public LinkedList<Integer> list = new LinkedList<>();
	public LinkedListToolset llts = new LinkedListToolset();
	public int insertNum;
	public int insertLoc;
	public int insnum;
	public int insloc;

	public void initalize(){
	llts.append(35);
	llts.append(36);
	llts.append(37);
	llts.append(38);
	llts.append(39);
	llts.append(40);
	llts.append(22);
	}

	public void display(){
	System.out.println("\nCurrent Array: ");
	llts.print();
	}

	public void getInput(){
	getInputLoc();
	//getInputNum();
	//System.out.println("insert " + insertNum + " Into position " + insertLoc);
	}


	public void getInputLoc(){
	Scanner scan = new Scanner(System.in);
	try{
			  System.out.println("Please input an integer:");
			  insertLoc=scan.nextInt();
			}
			catch(InputMismatchException exception2){
			  System.out.println("This is not an integer, 0 will be used in place.");
			}
	}
	public void getInputNum(){
	Scanner scan = new Scanner(System.in);
	/*System.out.println("Please enter a number to insert()");
	insertNum = scan.nextInt();
	*/
	 int insNum;
				    do {
				        System.out.println("Please enter a positive number!");
				        while (!scan.hasNextInt()) {
				            System.out.println("That's not a number!");
				            scan.next();
				        }
				        insNum = scan.nextInt();
				    } while (insNum <= 0);
    System.out.println("Thank you! Recieved: " + insNum);
	}

	public void insToArray(){
	llts.append(insertLoc);
	}

	public void delete(){
	System.out.println("Please enter an existing value to delete");
	Scanner scan = new Scanner(System.in);
			    int deleteNum;
			    do {
			        System.out.println("Please enter a positive number!");
			        while (!scan.hasNextInt()) {
			            System.out.println("That's not a number!");
			            scan.next();
			        }
			        deleteNum = scan.nextInt();
			    } while (deleteNum <= 0);
    System.out.println("Thank you! Recieved: " + deleteNum);
    llts.delete(deleteNum);
	}

		public void insanddelete(){
			//need to validate input is less than max size of our list length
		Scanner scan = new Scanner(System.in);
			    int number;
			    do {
			        System.out.println("Please enter a positive number!");
			        while (!scan.hasNextInt()) {
			            System.out.println("That's not a number!");
			            scan.next();
			        }
			        number = scan.nextInt();
			    } while (number <= 0);
    System.out.println("Thank you! Recieved: " + number);


		int number2;
					    do {
					        System.out.println("Please enter a positive number between 1 and 7");
					        while (!scan.hasNextInt()) {
					            System.out.println("That's not a number!");
					            scan.next();
					        }
					        number2 = scan.nextInt();
					    } while (number2 <= 0);{
							/* need to add case where user input is greater than the node's length*/
    System.out.println("Thank you! Recieved: " + number2);
	}
	llts.insertLoc(number,number2);
	}

	//search for position
	public void searchLocNonRec(){
		Scanner scan = new Scanner(System.in);
		int loc;
		do {
			System.out.println("Please enter a positive number!");
			while (!scan.hasNextInt()) {
			System.out.println("That's not a number!");
			scan.next();
			}
		loc = scan.nextInt();
		} while (loc <= 0);
    System.out.println("Thank you! Recieved: " + loc +"\n\n");
	llts.searchLocNonRec(loc);
}


public void searchLocRec(){
		Scanner scan = new Scanner(System.in);
			int loc2;
			do {
			System.out.println("Please enter a positive number!");
			while (!scan.hasNextInt()) {
			System.out.println("That's not a number!");
			scan.next();
			}
			loc2 = scan.nextInt();
		} while (loc2 <= 0);
llts.searchLocRecCall(loc2);
}




	//run program, driver calls. attempt to minimize driver code
	public void run(){
	initalize();
	display();
	getInput();
	insToArray();
	display();
	delete();
	display();
	insanddelete();
	display();

	//need to create input validation for these two
	//searchLocNonRec();
	//searchLocRec();

	}
}