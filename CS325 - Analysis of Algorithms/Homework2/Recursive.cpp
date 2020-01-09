#include <iostream>
#include <chrono>

int I = 1;
int l1[100];
int l2[100];
int l3[100];
int par[100];
int temp;
int temp2;
int smallcount = 0;
using namespace std;
int count = 1;
int currTower = 1;

void initTower(int A, int B, int C, int n) {


	l1[1] = { A };
	l2[1] = { B };
	l3[1] = { C };

	par[1] = { 1 };
	par[0] = { 1 };
	l1[0] = { 0 };
	l2[0] = { 1 };
	l3[0] = { 2 };
}
void runtower(int A, int B, int C, int n){


	while (I >= 1)
	{


		if (I != n - 1) {

			l1[I + 1] = l1[I];
			l2[I + 1] = l2[I];
			l3[I + 1] = l3[I];
			par[I + 1] = 1;
			I = I + 1;
			//cout << "whataboutthis\n";
			//cout << "decrease tower 3?\n";
			smallcount++;
		}

		else {
			if (smallcount >= 6) {
				//cout << "decrease tower 2\n";
				temp2 = l1[0];
				l1[0] = l3[0];
				l3[0] = l2[0];
				l2[0] = temp2;
				smallcount = 0;
				temp2 = l1[0];
				l1[0] = l3[0];
				l3[0] = l2[0];
				l2[0] = temp2;
			}

			while (par[I] == 2) {
				I = I - 1;
				//cout << "how many times does this hit\n";
				//cout << "decrease tower\n";
				temp2 = l1[0];
				l1[0] = l3[0];
				l3[0] = l2[0];
				l2[0] = temp2;
				
				if (smallcount >= 6) {
					//cout << "decrease tower 2\n";
					temp2 = l1[0];
					l1[0] = l3[0];
					l3[0] = l2[0];
					l2[0] = temp2;
					smallcount = 0;
				}
				

			}



			if (I >= 1) {

				//l2[I] = l1[I];
				::count++;


				cout << "move ring " << I << " to tower " << l3[0] << "\n";
				par[I] = 2;
				temp = l1[I];
				l1[I] = l3[I];
				l3[I] = l2[I];
				l2[I] = temp;
				

			}

		}

		runtower(A, B, C, n);
	}
}

int main()
{
	char exit = 3;

	int rings;

	cout << "recursive Hanoi\n\n";

	cout << "Please enter how many rings should be on the tower: ";

	cin >> rings;

	auto start = std::chrono::high_resolution_clock::now();
	initTower(1, 1, 1, rings + 1);
	runtower(1, 1, 1, rings + 1);
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "\nElapsed time: " << elapsed.count() << " s\n";

	cout << "\n\nCount of steps was: " << ::count;

	cout << "\n\npress any key and enter to continue";

	cin >> exit;

	return 0;

}