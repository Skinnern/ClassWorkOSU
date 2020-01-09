
public class BinarySearchTree {

	public static  Node root;

	//initalize our BST
	public BinarySearchTree(){
	//create the base of the tree to be null
	this.root = null;
	}
	//find
	//searches the tree for given value
	//returns type boolean, because we only need to know if it finds something or not
	public boolean find(int val){
		//set current node to root
		Node current = root;
		//if current node is not null
		while(current!=null){
		//and the current node is equal to the value the user has given
			if(current.data==val){
				return true;
				//return a positive
				//else search down the tree, set the current node to the root and search children, loop until value is found
			}else if(current.data>val){
				current = current.left;
			}else{
				current = current.right;
			}
		}
		//return false if value cannot be found
		return false;
	}
	//insert
	//insert into the binary search tree
	public void ins(int val){
		//create new node for variable
		Node newNode = new Node(val);
		if(root==null){
			//if root does not exist
			root = newNode;
			//assign our node to root
			//this will initiate our process
			return;
		}
		//our current node is our root
		Node current = root;
		//assign node parent to null initally, before we look down to the children
		Node parent = null;
		//while loop to look down to our children, determine where the variable should go, and place it there.
		while(true){
			parent = current;
			if(val<current.data){
				current = current.left;
				//place value on left
				if(current==null){
					parent.left = newNode;
					//return after variable is placed
					return;
				}
			}else{
				//place value on the right side
				current = current.right;
				if(current==null){
					//create a new node if that value is null
					parent.right = newNode;
					//end
					//return after variable is placed
					return;
				}
			}
		}
	}
	//display
	//need to get children and orgin node, how do i differentiate what tier the objects are at though...
	public void display(Node root){
		//if root is not null, go to the child
		if(root!=null){
			//the way this will display is that it will go from the lowest child, and print upward from that
			//making it print into sorted order from highest to lowest
			display(root.left);
			//return to root
			System.out.print(" \n" + root.data);
			//print out the object toward the right
			display(root.right);
		}
	}
}


