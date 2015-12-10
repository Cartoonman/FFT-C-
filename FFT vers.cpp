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
	int count = 10; // Adjust the initial val for matrix pumping
	// Initialize toeplitz (2n-1 distinct vals)
	for (int j = n-1; j > 0; j--){
		int l = 0;
		int p = j;
		while(p < n){
		setArrayVal(Toeplitz, p, l, count);
		l++;
		p++;
		}
		count = (count + 1)%32;
		}
	for (int i = 0; i < n; i++){
		int k = 0;
		int m = i;
		while(k < n-i){
		setArrayVal(Toeplitz, k, m, count);
		k++;
		m++;
		}
		count = (count + 1)%32;
	}	

	// Initialize pmatrix
	for (int lol = 0; lol < n; lol++){pmatrix[lol] = count++;}
		

	
	
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
	Complex *tfft = new Complex[c];
	Complex *pfft = new Complex[c];
	int i = 0;
	int u = b;
	
	//making the tpoly array. 
	while(u >= 0){
		tfft[i] = getArrayVal(Toeplitz, u, 0);
		u--;
		i++;
		}
	u = 1;
	while(u < n-1){
		tfft[i] = getArrayVal(Toeplitz, 0, u);
		u++;
		i++;
		}
	while(i <= c-1){
		tfft[i] = 0;
		i++;
		}
		
	// making the ppoly array
	i = 0;	
	while(i <= n-1){
		pfft[i] = pmatrix[n-1-i];
		i++;
		}
	while(i <= c-1){
		pfft[i] = 0;
		i++;
		}	
	
	

    CArray tft(tfft, c);
    CArray pft(pfft, c);

	Complex *rfft = new Complex[c];
    CArray rft(rfft, c);

	
	fft (tft);
	fft (pft);
			
			
			
	for(int i = 0; i < c; i++){
		rft[i] = tft[i]*pft[i];
		}
		
	ifft (rft);

	i = 0;
	int *result = new int [n];
	while(i != n){
		result[i] = (int)rft[n-1+i].real();
		i++;
		}
	cout << " OUTPUT: ";
		for (int lol = 0; lol < n; lol++){
		cout << result[lol] << " ";
		}	
    
	
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout<<"Time taken for Multiplying "<<n<<" dimentional matrix is : "<< duration <<" Seconds"<<'\n';
	
	return 0;
}