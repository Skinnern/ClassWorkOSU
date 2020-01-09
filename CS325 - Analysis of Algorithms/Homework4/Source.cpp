#include <iostream>
#include <stdlib.h>
using namespace std;


//char board[16][16];


//tiling game solver
//2^k * 2^k ~= double array [][]
//iterate to find 
int beginningSize = 0;

int totalSizeMethod(int entry) {
	int size = 2;
	int i = 0;
	while (entry - 1 > i) {
		size = size * 2;
		i++;
	}
	return size;
}

int giverand(int size) {
	int rando;
	rando = rand() % size;
	return rando;
}

void populateBoard(int size, int board[16][16]) {
	for (int i = 0; i<size; i++)    //This loops on the rows.
	{
		for (int j = 0; j<size; j++) //This loops on the columns
		{
			board[i][j] = 0;
		}
	}
}

void fillboard(int board[16][16], int currx, int curry, int blockx, int blocky, int size) {

	if (size == 1) {
		//board[currx][curry] = 1;
		//board[currx + 1][curry] = 1;
		//board[currx + 1][curry + 1] = 1;
		//board[currx][curry + 1] = 1;
		return;
	}

	int m = (size + 1) / 2;
	int cx = currx + m;
	int cy = curry + m;
	int mx1, mx2, mx3, mx4, my1, my2, my3, my4;
	if (blockx < cx && blocky < cy)
	{
		board[cx][cy] = 2;
		board[cx][cy - 1] = 2;
		board[cx - 1][cy] = 2;
		mx1 = blockx;
		my1 = blocky;
	}
	//four different block types:

	//one

	if (blockx < cx && blocky < cy) {
		board[cx][cy] = 2;
		board[cx][cy - 1] = 2;
		board[cx - 1][cy] = 2;
		mx1 = blockx;
		my1 = blocky;
	}
	else
	{
		mx1 = cx - 1; my1 = cy - 1;
	}

	//two

	if (blockx < cx && blocky >= cy)
	{
		board[cx - 1][cy - 1] = 3;
		board[cx][cy - 1] = 3;
		board[cx][cy] = 3;
		mx2 = blockx;
		my2 = blocky;
	}
	else
	{
		mx2 = cx - 1; my2 = cy;
	}

	//three

	if (blockx >= cx && blocky < cy)
	{
		board[cx - 1][cy - 1] = 4;
		board[cx - 1][cy] = 4;
		board[cx][cy] = 4;
		mx3 = blockx;
		my3 = blocky;
	}
	else
	{
		mx3 = cx; my3 = cy - 1;
	}

	//four

	if (blockx >= cx && blocky >= cy)
	{
		board[cx - 1][cy - 1] = 5;
		board[cx][cy - 1] = 5;
		board[cx - 1][cy] = 5;
		mx4 = blockx;
		my4 = blocky;
	}
	else
	{
		mx4 = cx;
		my4 = cy;
	}

	int newx = currx + m;
	int newy = curry + m;

	fillboard(board, currx, curry, mx1, my1, m);
	fillboard(board, currx, curry + m, mx2, my2, m);
	fillboard(board, currx + m, curry, mx3, my3, m);
	fillboard(board, currx + m, curry + m, mx4, my4, m);
}

void printBoard(int size, int board[16][16]) {
	cout << "\n\n";
	for (int i = 0; i<size; i++)    //This loops on the rows.
	{
		for (int j = 0; j<size; j++) //This loops on the columns
		{
			cout << board[i][j] << ", ";
		}
		cout << "\n";
	}
}

void placeOne(int one, int two, int board[16][16]) {
	board[one][two] = 1;
}

int main()
{
	int board[16][16];
	int size;
	int pos1;
	int pos2;
	//int beginningSize;
	cout << "Please enter a number for grid size ( will end up in a 2^k):\n";
	cin >> size;
	//generate size needed
	size = totalSizeMethod(size);
	pos1 = giverand(size);
	cout << pos1;
	pos2 = giverand(size);
	cout << pos2;
	cout << size;
	populateBoard(size, board);
	placeOne(pos1, pos2, board);
	//board[1][1] = 1;
	printBoard(size, board);
	fillboard(board, 0, 0, pos1, pos2, size);
	printBoard(size, board);

	cin >> size;
	return 0;
}

