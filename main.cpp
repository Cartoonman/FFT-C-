#include <iostream>
#include <cstdio>
#include <complex>
#include <valarray>
#include <ctime>
using namespace std;
const double PI = 3.141592653589793238460;
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

/***************************/
int n = 10;  // width and height of the matrix
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
	
	
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;
 
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
 
    // conquer
    fft(even);
    fft(odd);
 
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    fft( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}
			
	


int main(){
	std::clock_t start;
    double duration;
	start = std::clock();
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
	
	
	// Matrix Multi w/ FFT
	
	unsigned int a = 2*n-1;
	unsigned int b = n-1;
	unsigned int c = a+b;

	//round to nearest power of 2 for efficient fft
	c--;
	c |= c >> 1;
	c |= c >> 2;
	c |= c >> 4;
	c |= c >> 8;
	c |= c >> 16;
	c++;
	
	
	// initialize arrays for fft. c is next highest power of 2 of our polys for fft.
	int *tpoly = new int[c]; //toeplitz 
	int *ppoly = new int[c]; //vector
	int *rpoly = new int[c]; //result
	int i = 0;
	int u = b;
	
	//making the tpoly array. 
	while(u >= 0){
		cout << u << endl;
		tpoly[i] = getArrayVal(Toeplitz, u, 0);
		u--;
		i++;
		}
	u = 1;
	while(u < n-1){
		tpoly[i] = getArrayVal(Toeplitz, 0, u);
		u++;
		i++;
		}
	while(i <= c-1){
		tpoly[i] = 0;
		i++;
		}
		
	// making the ppoly array
	i = 0;	
	while(i <= n-1){
		ppoly[i] = pmatrix[n-1-i];
		i++;
		}
	while(i <= c-1){
		ppoly[i] = 0;
		i++;
		}	
		
	cout << " TARR: ";	
	for (int lol = 0; lol < c; lol++){
		cout << tpoly[lol] << " ";
		}
	cout << endl;
	cout << " PARR: ";	
	for (int lol = 0; lol < c; lol++){
		cout << ppoly[lol] << " ";
		}		
	cout << endl;
	
	
	Complex *tfft = new Complex[c];
	for (int lol = 0; lol < c; lol++){
		tfft[lol] = tpoly[lol];
		}
    CArray tft(tfft, c);
	
	
	Complex *pfft = new Complex[c];
	for (int lol = 0; lol < c; lol++){
		pfft[lol] = ppoly[lol];
		}
    CArray pft(pfft, c);

	
	
	Complex *rfft = new Complex[c];
	for (int lol = 0; lol < c; lol++){
		rfft[lol] = 0;
		}
    CArray rft(rfft, c);

	
	fft (tft);
	fft (pft);
	
		for (int lol = 0; lol < c; lol++){
		cout << tft[lol] << " ";
		}
		cout << endl;
		
		for (int lol = 0; lol < c; lol++){
		cout << pft[lol] << " ";
		}
		cout << endl;
			
			
			
	for(int i = 0; i < c; i++){
		rft[i] = tft[i]*pft[i];
		}
		for (int lol = 0; lol < c; lol++){
		cout << rft[lol] << " ";
		}
		cout << endl;
		
	ifft (rft);

	cout << " OUTPUT: ";	
	for (int lol = 0; lol < c; lol++){
		cout << rft[lol] << " ";
		}		
	cout << endl;
	
    
	
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
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout<<"Time taken for Multiplying "<<n<<" dimentional matrix is : "<< duration <<" Seconds"<<'\n';
	
	return 0;
}