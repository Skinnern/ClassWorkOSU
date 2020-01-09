// multiply two polynomials

#include <iostream>
#include <stdlib.h>
using namespace std;

int *multiply(int A[], int B[], int n, int m)
{


	int *prod = new int[m + n - 1];

	// Initialize the porduct polynomial
	for (int i = 0; i<m + n - 1; i++)
		prod[i] = 0;

	// Multiply two polynomials term by term

	// Take ever term of first polynomial
	for (int i = 0; i<m; i++)
	{
		// Multiply the current term of first polynomial
		// with every term of second polynomial.
		for (int j = 0; j<n; j++)
			prod[i + j] += A[i] * B[j];
	}

	return prod;
}


void printPoly(int poly[], int n)
{
	for (int i = 0; i<n; i++)
	{
		cout << poly[i];
		if (i != 0)
			cout << "x^" << i;
		if (i != n - 1)
			cout << " + ";
	}
}


int main()
{
	int size;
	int test_poly1[] = {3, 2, 1};
	int test_poly2[] = { 1, 2, 3 };

	int test_poly3[] = { 4, 3, 2, 1 };
	int test_poly4[] = { 1, 2, 3, 4 };

	int test_poly5[] = { 5, 4, 3, 2, 1 };
	int test_poly6[] = { 1, 2, 3, 4, 5 };

	int m = sizeof(test_poly1) / sizeof(test_poly1[0]);
	int n = sizeof(test_poly2) / sizeof(test_poly2[0]);


	int *prod = multiply(test_poly1, test_poly4, n, m);
	printPoly(prod, m + n - 1);
	cin >> size;
	return 0;

}