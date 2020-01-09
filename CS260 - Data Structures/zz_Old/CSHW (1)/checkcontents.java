//check contents
public class checkcontents{
int[] MyArray ={3,8,4,1,99,-2,44,6,3,2,7};

public static void main(String[] args){
checkcontents chk = new checkcontents();
chk.run();



}

public void run(){
initalize();
lookthrough();
}

public void initalize(){
System.out.println("Looking for value 6 in our array\n\nOur current array contents:\n");
printarr();

}

public void printarr(){
for(int i = 0;i<MyArray.length;i++)
{System.out.print(MyArray[i] + " ");
}

}



public void lookthrough(){
	for(int j = 0;j<MyArray.length;j++){
		if(MyArray[j]==6){
		System.out.println("we got a 6");
	}
		else{
			System.out.println("This is not a 6");
		}


	}
}


}