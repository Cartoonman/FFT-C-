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
	int *pmatrix = new int[n];
	int count = 10;
	
	// Initialize toeplitz (2n-1 distinct vals)
	for (int j = n-1; j > 0; j--){
		int l = 0;
		int p = j;
		while(p < n){
		setArrayVal(Toeplitz, p, l, count);
		l++;
		p++;
		}
		count++;
		}
	for (int i = 0; i < n; i++){
		int k = 0;
		int m = i;
		while(k < n-i){
		setArrayVal(Toeplitz, k, m, count);
		k++;
		m++;
		}
		count++;
	}	

	// Initialize pmatrix
	for (int lol = 0; lol < n; lol++){pmatrix[lol] = count++;}
		
		
	for (int lol = 0; lol < n; lol++){
		cout << pmatrix[lol] << endl;
		}
		cout << endl;
		
	// MATRIXMULTIP O(n^2)
	int *result = new int[n];
	int	tempsum;
	for (int i = 0; i < n; i++){
		tempsum = 0;
		for (int j = 0; j < n; j++){
			tempsum += Toeplitz[i + j*n] * pmatrix[j];
		}
		result[i] = tempsum;
	}
	
	
	// prints topelitz matrix
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << getArrayVal(Toeplitz, i, j) << " ";
			}
		cout << endl;
		}
	
		cout << "RESULT: ";
	for (int lol = 0; lol < n; lol++){
		cout << result[lol] << " ";
		}
		cout << endl;
	
	/*
	setArrayVal(Toeplitz, 2, 1, 5);

	int x = getArrayVal(Toeplitz, 2, 1);
	
	cout << x << endl;
	
	delete[] Toeplitz; //delete
	*/
	
	
	
	return 0;
}
