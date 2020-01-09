#include<stdio.h>
#include <random>
#include <time.h>

//the assignment says to use n*m, but it also said
//that we can assume that n=m, so we only declare N

#define knightMovement 8

//definitions to change for testing:
#define N 8
#define J 1
#define I 1

//these are the movment pattens for the knight
static int CheckX[knightMovement] = { 1,1,2,2,-1,-1,-2,-2 };
static int CheckY[knightMovement] = { 2,-2,1,-1,2,-2,1,-1 };

bool limits(int x, int y);
bool isempty(int a[], int x, int y);
int getDegree(int a[], int x, int y);
bool nextMove(int a[], int *x, int *y);
void print(int a[]);
bool neighbour(int x, int y, int xx, int yy);
bool findClosedTour();
//main
int main()
{
	// To make sure that different random
	// initial positions are picked.
	srand(time(NULL));

	// While we don't get a solution
	while (!findClosedTour())
	{
		;
	}
	return 0;
}

// function restricts the knight to remain within
// the 8x8 chessboard
bool limits(int x, int y)
{
	return ((x >= 0 && y >= 0) && (x < N && y < N));
}

/* Checks whether a square is valid and empty or not */
bool isempty(int a[], int x, int y)
{
	return (limits(x, y)) && (a[y*N + x] < 0);
}

/* Returns the number of empty squares adjacent
to (x, y) */
int getDegree(int a[], int x, int y)
{
	int count = 0;
	for (int i = 0; i < N; ++i)
		if (isempty(a, (x + CheckX[i]), (y + CheckY[i])))
			count++;

	return count;
}

// Picks next point using Warnsdorff's heuristic.
// Returns false if it is not possible to pick
// next point.
bool nextMove(int a[], int *x, int *y)
{
	int min_deg_idx = -1, c, min_deg = (N + 1), nx, ny;

	// Try all N adjacent of (*x, *y) starting
	// from a random adjacent. Find the adjacent
	// with minimum degree.
	int start = rand() % N;
	for (int count = 0; count < N; ++count)
	{
		int i = (start + count) % N;
		nx = *x + CheckX[i];
		ny = *y + CheckY[i];
		if ((isempty(a, nx, ny)) &&
			(c = getDegree(a, nx, ny)) < min_deg)
		{
			min_deg_idx = i;
			min_deg = c;
		}
	}

	// IF we could not find a next cell
	if (min_deg_idx == -1)
		return false;

	// Store coordinates of next point
	nx = *x + CheckX[min_deg_idx];
	ny = *y + CheckY[min_deg_idx];

	// Mark next move
	a[ny*N + nx] = a[(*y)*N + (*x)] + 1;

	// Update next point
	*x = nx;
	*y = ny;

	return true;
}

/* displays the chessboard with all the
legal knight's moves */
void print(int a[])
{
	for (int i = 0; i < N; ++i)
	{
		for (int q = 0; q < N; ++q)
			printf("%d\t", a[q*N + i]);
		printf("\n");
	}
}

/* checks its neighbouring sqaures */
/* If the knight ends on a square that is one
knight's move from the beginning square,
then tour is closed */
bool neighbour(int x, int y, int xx, int yy)
{
	for (int i = 0; i < N; ++i)
		if (((x + CheckX[i]) == xx) && ((y + CheckY[i]) == yy))
			return true;

	return false;
}

/* Generates the legal moves using warnsdorff's
heuristics. Returns false if not possible */
bool findClosedTour()
{
	// Filling up the chessboard matrix with -1's
	int a[N*N];
	for (int i = 0; i< N*N; ++i)
		a[i] = -1;

	// Randome initial position
	//int j = rand() % N;
	//int I = rand() % N;

	// Current points are same as initial points
	int x = J, y = I;
	a[y*N + x] = 1; // Mark first move.

					// Keep picking next points using
					// Warnsdorff's heuristic
	for (int i = 0; i < N*N - 1; ++i)
		if (nextMove(a, &x, &y) == 0)
			return false;

	// Check if tour is closed (Can end
	// at starting point)
	if (!neighbour(x, y, J, I))
		return false;

	print(a);
	return true;
}
