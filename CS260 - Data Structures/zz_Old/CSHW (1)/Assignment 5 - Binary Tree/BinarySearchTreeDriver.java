import java.util.Scanner;
public class BinarySearchTreeDriver{

	public static void main(String arg[]){
		BinarySearchTree bst = new BinarySearchTree();
		//allow user to input int to search for in tree
		Scanner scan = new Scanner(System.in);
		//Insert some values into our tree
		bst.ins(37);
		bst.ins(8);
		bst.ins(6);
		bst.ins(7);
		bst.ins(5);
		bst.ins(3);
		bst.ins(0);
		bst.ins(9);

		//display our tree
		System.out.println("Original Tree : ");
		bst.display(bst.root);
		System.out.println();
		System.out.println("Please enter a value you would like to search the tree for:");
		//does not have input validation, will crash if unapproved value is placed into the node.
		int findval;
		findval = scan.nextInt();
		//check if a value that the user has given exists within our tree

		System.out.println("does the value " + findval +" exist in the tree? : " + bst.find(findval));

		//display our tree
		bst.display(bst.root);
		System.out.println();
	}
}


/*
	public void findvar(){
		System.out.println("Please enter a number you would like to search for");

		int findval;

		find(findval);

	}
*/