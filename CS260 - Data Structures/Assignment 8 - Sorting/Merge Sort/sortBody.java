public class sortBody{
	public int[] MyArray = {2,8,4,1,7,3,9,5};
	public int[] tempArray = new int[MyArray.length];
	public int[] tempArrayb = new int[MyArray.length];

	public void displayArray(){
		System.out.println("Current Array: \n");
		for(int i = 0; i < MyArray.length; i++){
			System.out.print(MyArray[i] + " ");
		}
		System.out.println();
	}

	public void displayTempArray(){
		System.out.println("Current Array: \n");
		for(int i = 0; i < tempArray.length; i++){
			System.out.print(tempArray[i] + " ");
		}
		System.out.println();
	}

	public void run(){

		runSort();
		displayArray();
	}

	public void runSort(){
		displayArray();
		LowestLevel();
		displayArray();
		MiddleLevel();
		displayArray();
		HighLevel();
		displayArray();
	}

	public void LowestLevel(){
		int tempa;
		int tempb;
		int tempc;
		int b4;
		int f;
		tempc = MyArray.length/2;

		for(int z = 0; z<tempc;z++){
			f = z*2;
			b4 = f+1;
			tempa = MyArray[f];
			tempb = MyArray[b4];

			if(tempa>tempb){
				//System.out.println("ffff");
				tempArray[f]= tempb;
				tempArray[b4]=tempa;
				System.out.print(tempArray[f] + " "+ tempArray[b4]+ "|");
			}else{
				tempArray[f]= tempa;
				tempArray[b4]=tempb;
				System.out.print(tempArray[f] + " "+ tempArray[b4] + "|");
			}
		}
		System.out.println();
		merge();
	}

	public void MiddleLevel(){
		int tempa;
		int tempb;
		int tempc;
		int tempd;
		int tempe;
		int b4;
		int b5;
		int b6;
		int b7;
		int f;
		tempc = MyArray.length/2;
		tempc = tempc/2;

		for(int t=0; t!=2; t++){
			f = t*4;
			b5 = f+1;
			b6 = f+2;
			b7 = f+3;
			int nss = f+4;

			for(int g = f; g < nss; g++){
				if(MyArray[f]<MyArray[b5]&&MyArray[f]<MyArray[b6]&&MyArray[f]<MyArray[b7]){
					//SET TO G POSITION ON ARRAY
					tempArray[g] = MyArray[f];
					MyArray[f]=1111;
				}
				else if(MyArray[b5]<MyArray[f]&&MyArray[b5]<MyArray[b6]&&MyArray[b5]<MyArray[b7]){
					//SET TO G POSITION ON ARRAY
					tempArray[g] = MyArray[b5];
					MyArray[b5]=2222;
				}
				else if(MyArray[b6]<MyArray[f]&&MyArray[b6]<MyArray[b5]&&MyArray[b6]<MyArray[b7]){
					//SET TO G POSITION ON ARRAY
					tempArray[g] = MyArray[b6];
					MyArray[b6]=3333;
				}
				else if(MyArray[b7]<MyArray[f]&&MyArray[b7]<MyArray[b5]&&MyArray[b7]<MyArray[b6]){
					//SET TO G POSITION ON ARRAY
					tempArray[g] = MyArray[b7];
					MyArray[b7]=4444;
				}
			}
		}
		merge();
	}

	public void HighLevel(){
	for (int i = 0; i<MyArray.length; i++)
		{
			for (int j = 0; j<MyArray.length; j++)
			{
				if (MyArray[i] < MyArray[j])
				{
					int temp = MyArray[i];
					MyArray[i] = MyArray[j];
					MyArray[j] = temp;
				}
			}
		}
	}

	public void merge(){
		for(int i = 0; i < MyArray.length; i++){
			MyArray[i] = tempArray[i];
		}
		System.out.println("merged the arrays");
	}
}