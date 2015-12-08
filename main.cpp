#include <iostream>
using namespace std;

/***************************/
int n = 5;  // width and height of the matrix
/****************************/

//Functions
int getArrayVal(int*, int, int);
void setArrayVal(int*, int, int, int);


int getArrayVal(int *mat, int row, int col){
	return mat[row + col*n];
	}

void setArrayVal(int *mat, int row, int col, int val){
	mat[row + col*n] = val;
	}
	


int main(){

	int *Toeplitz = new int[n*n];
	int count = 10;
	// Initialize toeplitz 
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			setArrayVal(Toeplitz, i, j, count);
			count++;
			}
		}
			
	
	
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << getArrayVal(Toeplitz, i, j) << " ";
			}
		cout << endl;
		}
	
	
	
	/*
	setArrayVal(Toeplitz, 2, 1, 5);

	int x = getArrayVal(Toeplitz, 2, 1);
	
	cout << x << endl;
	
	delete[] Toeplitz; //delete
	*/
	
	
	
	return 0;
}
