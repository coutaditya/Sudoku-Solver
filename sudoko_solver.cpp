// The given program solves a 9X9 sudoko.

#include<bits/stdc++.h>

#define int long long int
#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>

using namespace :: std;

// Prints the sudoko
void printSudoko(vector<vector<int> > sudoko){
	for(auto i:sudoko){
		for(auto j:i){
			cout<<j<<" ";
		}
		cout<<"\n";
	}
}

// Checks if a value is allowed at a given cell (x, y)
bool isAllowed(vector<vector<int> > sudoko, int x, int y, int val){
	// check if the cloumn has val already
	for(int i=0; i<9; i++){
		if(sudoko[i][y]==val){
			return false;
		}
	}

	// check if the row has val already
	for(int i=0; i<9; i++){
		if(sudoko[x][i]==val){
			return false;
		}
	}

	// check if the sub grid (3X3 matrix) of the current cell has the val already
	int xx = (x/3)*3;   // --> starting row index of current cell subgrid
	int yy = (y/3)*3;	// --> starting column index of current cell subgrid

	for(int i=xx; i<xx+3; i++){
		for(int j=yy; j<yy+3; j++){
			if(sudoko[i][j]==val){
				return false;
			}
		}
	}

	return true;
}

bool solveSudoko(vector<vector<int> > sudoko, int i, int j){
	// Base Case: Print the sudoko when you've reached the end of all rows (0-8)
	if(i==9){
        cout<<"Solution:\n";
		printSudoko(sudoko);
		return true;
	}

	// Move to the next row when you reach the end of a row
	if(j==9){						
		return solveSudoko(sudoko, i+1, 0);
	}

	// If the current cell is already filled, move to the next cell
	if(sudoko[i][j]!=0){
		return solveSudoko(sudoko, i, j+1);
	}

	for(int val=1; val<=9; val++){
		if(isAllowed(sudoko, i, j, val)){
			sudoko[i][j]=val;
			int success = solveSudoko(sudoko, i, j+1);  // returns if solution if possible the remaining sudoko with current val placed at (i, j)
			if(success){
				return true;
			}
			sudoko[i][j]=0;   // backtrack if the solution is not found
		}
	}

	return false;
}

int32_t main(){

    cout<<"Enter the sudoko that you wish to solve:\n";
    cout<<"(Enter 0 to denote the spaces)\n";

    /* Sample sudoko to use:    5 3 0 0 7 0 0 0 0
                                6 0 0 1 9 5 0 0 0
                                0 9 8 0 0 0 0 6 0
                                8 0 0 0 6 0 0 0 3
                                4 0 0 8 0 3 0 0 1
                                7 0 0 0 2 0 0 0 6
                                0 6 0 0 0 0 2 8 0
                                0 0 0 4 1 9 0 0 5
                                0 0 0 0 8 0 0 7 9   */

	vector<vector<int> > sudoko(9, vector<int>(9, 0));
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			cin>>sudoko[i][j];
		}
	}

	bool solution = solveSudoko(sudoko, 0, 0);

	if(solution==false){
		cout<<"The entered sudoko does not have a possible solution!";
	}

	return 0;
}