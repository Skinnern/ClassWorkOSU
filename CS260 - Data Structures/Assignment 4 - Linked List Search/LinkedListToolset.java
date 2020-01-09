//create a list that automatically inserts values into the correct position, efficently searches for elements and commpares a recursive and non-recursive solution
import java.util.Scanner;
//toolset for most things having to do with the linkedlist
class LinkedListToolset {
//head is the beginning of our list
private Node head = null;
public int recursivecomp;
public int nonrecursivecomp;

       //getLastNode is useful for my other methods, it just peeks for the most recent node and returns the .next value
       private Node getLastNode() {
           if (head == null) {
           return null;
           }
           Node tmpNode = head;
           while (tmpNode.next != null) {
           tmpNode = tmpNode.next;
           }
           return tmpNode;
   		}

   //append will add to the end of the linkedlist
	   public void append(int val) {
			Node lastNode = getLastNode();
			//a check to see if we're at the end of the list.
			if (lastNode == null) {
				//add newnode as user's input
				head = new Node(val);
			} else {
				//go to next
				lastNode.next = new Node(val);
			}
		}
	//delete will delete from a specified position
		public void delete(int val) {
			//check for beginning of linkedlist
			if(head == null){
				return;
			}
			Node prevNode = null;
			Node currNode = head;
			//iterate through the list
			while (currNode != null && currNode.num != val) {
				prevNode = currNode;
				currNode = currNode.next;
			}
			//check if 1st part is being deleted
			if(prevNode == null){
				head = head.next;
				return;
			}
			//check for blank
			if (currNode == null) {
				System.out.println("no value in node.");
				return;
			}
			//set variable prevNode.next to refer to a new value removing the currNode.num references altogether
			prevNode.next = currNode.next;
		}
    //print will loop and print all the contents of the linked list
		public void print() {
			System.out.println("");
			//check for empty
			if(head == null){
				System.out.print("EMPTY");
				return;
			}
			Node tmpNode = head;
			//iterate through until we find a null node, this will print every value along the way
			while (tmpNode != null) {
				System.out.print(tmpNode.num + ", ");
				tmpNode = tmpNode.next;
			}
   		}

//supposed to replace an already existing value in x position with a new value you set, a few issues came up during testing, but after a few fixes I believe its fine now
		public void insertLoc(int var, int loc) {
			//we use loc-1 to get the position right before our replace location, to replace the reference node
			int tempa = loc-1;
			Node trump =null ;
			Node prevNode = head;
			Node currNode = head;
			Node trumpNode = new Node(0);
			//parse through the loop searching for the user's desired position
			for (int i=0; i != tempa; i++) {
			currNode = currNode.next;
			}
			//setting things to equal a temp node so we can sever all connections to the previous before we insert our new one
			trump = currNode.next;
			trumpNode.num = var;
			trumpNode.next = trump;
			currNode.next = trumpNode.next;
			currNode.num = trumpNode.num;
		}

		//create a list that automatically inserts values into the correct position, efficently searches for elements and commpares a recursive and non-recursive solution
		//correct position is relative, do we want lowest to maximum? or do we want
		public void searchLocRecCall(int loc){
		Node tmpNode = head;
		int i = 0;
		searchLocRecFunc(loc, i, tmpNode);
		}

		//this is the actual recursive function that it will run through
		public int searchLocRecFunc(int loc, int i, Node tmpNode){
			if(i < loc-1){
				tmpNode = tmpNode.next;
				i++;
				return searchLocRecFunc(loc, i, tmpNode);
			}
				else{
					System.out.println("value at this location is " + tmpNode.num + "\nand the number of comparisons is: " + i);
		}

		return loc;
		}

		//nonrecursivesearch,just counts up the loop with a for statment then displays comparisons
		public void searchLocNonRec(int loc){

					Node tmpNode = head;
					for (int i=0; i != loc-1; i++) {
					tmpNode = tmpNode.next;
					recursivecomp++;
					}
			System.out.println("value at that position is: " + tmpNode.num + " \nThis took " + recursivecomp+" comparison(s).");
		}

}