#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int UniqueSols = 100;
int UniqueSolsArr[UniqueSols];

//this appears to solve up to 7 total n's until i get a space issue that seems to scroll the answers too far off screen. I'm not sure what is causing this bug.


// The method prototypes
bool isomorphic_unique(const vector<int>& queens, int N);
void n_queens(int n);
void backtrack(vector<int>&, int current_row, int N);
bool construct_candidates(const vector<int>&, int row, int N, vector<int>&);
bool is_safe_square(const vector<int>&, int row, int col, int N);
bool is_solution(const vector<int>&, int N);
void print_solution(const vector<int>&, int N);

int main()
{
	int nick;
	int n;
	cout << "Please enter the N value:";
	cin >> n;
	n_queens(n);
	cin >> nick;
	return 0;
}

//iso-morphic checker
//we will want to take a newly constructed solution to the problem, and check that its not just a mirrored version of an already established solution
bool isomorphic_unique(const vector<int>& queens, int N){
	//I ran out of time trying to implement a standard implementation, so I made an alternative, where 
	
	//find blank spot in array
	//cout << UniqueSolsArr[0];
	int k = 0;
	while (UniqueSolsArr[k] != 0){
		//cout << UniqueSolsArr[0]
		k++;
	}

	//calculate total
	int Total = 0;
	for (int i = 0; i<N; ++i)
	{
		for (int j = 0; j<N; ++j)
		{
			if (queens[i] == j) { 
				Total = Total + i + j;
				//cout << "Current Total = " << Total;
			}
			else {}
		}
		cout << endl;
	}



	//check the arrays leading up to that point
	//if it is not found, make a new position for it.
	for (int i = 0; i < k; i++){
		//cout << k-1;
		//cout << "comparing array " << UniqueSolsArr[k-1] << " To our Total: " << Total << "\n\n";
		if (UniqueSolsArr[k-1] == Total){
			
			return false;
		}
	}



	UniqueSolsArr[k] = Total;
	//cout << "Total into array " << UniqueSolsArr[k] << "\n\n";
	return true;
}



void n_queens(int n)
{
	vector<int> queens = vector<int>();
	backtrack(queens, 0, n);
}

void backtrack(vector<int>& queens, int current_row, int N)
{
	// check if the configuration is solved
	if (is_solution(queens, N))
	{
		//cout << N;
		if (isomorphic_unique(queens, N) == true){
			print_solution(queens, N);
		}
	}
	else
	{
		// construct a vector of valid candidates
		vector<int> candidates = vector<int>();
		if (construct_candidates(queens, current_row, N, candidates))
		{
			for (int i = 0; i < candidates.size(); ++i)
			{
				// Push this in the partial solution and move further
				queens.push_back(candidates[i]);
				backtrack(queens, current_row + 1, N);
				// If no feasible solution was found then we ought to remove this and try the next one
				queens.pop_back();
			}
		}
	}
}

bool construct_candidates(const vector<int>& queens, int row, int N, vector<int>& candidates)
{
	// Returns false if there are no possible candidates, we must follow a different
	// branch if this so happens
	for (int i = 0; i<N; ++i)
	{
		if (is_safe_square(queens, row, i, N))
		{
			// Add a valid candidate, this can be done since we pass candidates by reference
			candidates.push_back(i);
		}
	}
	return candidates.size() > 0;
}

bool is_safe_square(const vector<int>& queens, int row, int col, int N)
{
	for (int i = 0; i<queens.size(); ++i)
	{
		// case when the queens are already placed in the same row or column
		if (i == row || queens[i] == col) return false;
		// case when there is a diagonal threat
		// remember! y = mx + c for a diagonal m = 1 therefore |x2 - x1| = |y2 - y1|
		if (abs(i - row) == abs(queens[i] - col)) return false;
	}
	//Returns true when no unsafe square is found
	//handles the case when there are no queens on the board trivially
	return true;
}

bool is_solution(const vector<int>& queens, int N)
{
	return queens.size() == N;
}

void print_solution(const vector<int>& queens, int N)
{
	for (int i = 0; i<N; ++i)
	{
		for (int j = 0; j<N; ++j)
		{
			if (queens[i] == j) { cout << 'Q'; }
			else { cout << '_'; }
		}
		cout << endl;
	}

	cout << "\nNon Mirrored Solution\n\n";
}