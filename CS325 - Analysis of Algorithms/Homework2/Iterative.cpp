#include <iostream>
#include <chrono>

using namespace std;
int count = 1;
int currTower = 1;
void iterTower(int A, int B, int C, int n) {
	int I = 1;
	int l1[100];
	int l2[100];
	int l3[100];
	int par[100];
	int temp;
	int temp2;
	int smallcount = 0;
	l1[0] = { 0 };
	l2[0] = { 1 };
	l3[0] = { 2 };
	l1[1] = { A };
	l2[1] = { B };
	l3[1] = { C };


	par[1] = { 1 };
	par[0] = { 1 };

	while (I >= 1)
	{

		if (I != n - 1) {
			l1[I + 1] = l1[I];
			l2[I + 1] = l2[I];
			l3[I + 1] = l3[I];
			par[I + 1] = 1;
			I = I + 1;


		}

		else {

			while (par[I] == 2) {
				I = I - 1;
				temp2 = l1[0];
				l1[0] = l3[0];
				l3[0] = l2[0];
				l2[0] = temp2;
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

	}
}

int main()
{
	char exit = 3;

	int rings;

	cout << "Iterative Hanoi\n\n";

	cout << "Please enter how many rings should be on the tower: ";

	cin >> rings;

	auto start = std::chrono::high_resolution_clock::now();
	iterTower(1, 1, 1, rings + 1);
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "\nElapsed time: " << elapsed.count() << " s\n";

	cout << "\n\nCount of steps was: " << ::count;

	cout << "\n\npress any key and enter to continue";

	cin >> exit;

	return 0;

}