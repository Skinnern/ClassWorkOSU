import java.util.Arrays;
public class HashFunction {

	String[] MyArray;
	int arraySize;
	int itemsInArray = 0;

	public static void main(String[] args) {

		HashFunction HashFunk = new HashFunction(30);
		//create and populate an array with various strings of 3 letters
		String[] AddingObjects = { "aaa", "bbb", "ccc", "ddd", "eee", "fff",
				"ggg", "hhh", "iii", "jjj", "kkj", "lll", "mmm", "nnn", "ooo",
				"ppp", "qqq", "rrr", "sss", "ttt", "uuu", "gr", "b", "m",
				"i", "r", "ee", "of", "ff", "ski" };
				//****note, hardcoded to hold only 30 values,
		//run hashfunction to add these to the hashtable
		HashFunk.hashFunction(AddingObjects, HashFunk.MyArray);
		//print the stack out
		HashFunk.displayTheStack();
	}
	//function to find position for the new values, if a desired position is already taken, then it will look toward the next
	public void hashFunction(String[] stringsForArray, String[] MyArray) {

		for (int n = 0; n < stringsForArray.length; n++) {

			String newElementVal = stringsForArray[n];
			//convert string into integer, for easier storage, then push it into our function

			//beginning
			String s = newElementVal;
			String t = "";
			//int f = 0;
			int m;
			//finds location from a, returns as string
			for (int i = 0; i < s.length(); ++i) {
			    char ch = s.charAt(i);
			    int nz = (int)ch - (int)'a' + 1;
			    t += String.valueOf(nz);
			}
			//loops until whole number is created from values I.e. "aaa" becomes 111
			m = Integer.parseInt(t);
			//grabs int value from string t
			System.out.println("The Number "+m+" was created.");
			//prints out new int that was gained from m
			//ending


			//arbitrary location finder
			int arrayIndex = m % 20;

			System.out.println("new index position = " + arrayIndex + " for value " + newElementVal);
			//check our table for if there is something in the position that this item wants
			/*while (MyArray[arrayIndex] != "-1") {
				++arrayIndex;
				//if item found, proceed to next location
				System.out.println("There was a collision, trying " + arrayIndex + " instead");
				arrayIndex %= arraySize;
			}*/
			//assign value to be new element in our hash table

			MyArray[arrayIndex] = newElementVal;

		}

	}
	//our hash function, recieves size for array to be
	HashFunction(int size) {
		arraySize = size;
		MyArray = new String[size];
		Arrays.fill(MyArray, "-1");
	}

	public void displayTheStack() {
		int inc = 0;
		//iterate through to print all the values
		for (int m = 0; m < 3; m++) {
			inc += 10;
			//print top row
			//break to nextline
			System.out.println();
			//print out position header (1, 2, 3, 4, etc.)
			for (int n = inc - 10; n < inc; n++) {
				System.out.format("| %3s " + " ", n);
			}
			//return to next line
			System.out.println();
			//loop to print divider for next line
			for (int n = 0; n < 71; n++){
				System.out.print("-");
			}

			System.out.println();
			//print values in the array in their appropriate position
			for (int n = inc - 10; n < inc; n++) {
					System.out.print(String.format("| %3s " + " ", MyArray[n]));
			}
			System.out.println();
		}

	}

}