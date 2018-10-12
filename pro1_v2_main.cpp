#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "pro1_v2.cpp"
using namespace std;

void createMatrix(int**, int , int);
void createMatriFile(int**, int, int);
void readMatriFile(ifstream&, int**, int, int);
void twoDPeak_v1(int**, vector<int>&, vector<int>&, int, int);
void outputPeak(ostream&, vector<int>&);

int main(int argc, char* argv[]) {
	ifstream input("TA_matrix_1.data");
	int row, col;
	// set the value of row and col from input file
	if(input.is_open()) {
		input >> row;
		input >> col;
	} else {
		cerr << "cannot open file";
	}	
	// create a 2D matrix by allocating dynamic array
	int** a = new int* [row];	
	for(int i = 0; i < row; i++) {
		a[i] = new int[col];
	}
	// cout << row << " " << col; 
	
	readMatriFile(input, a, row, col);
	//createMatrix(a, row, col);
	//createMatriFile(a, row, col);
	// srand(time(NULL));
	// clock_t begin, end;
	// double timeSpent;
	// begin = clock();
	vector<int> rowVec, peakSet;
	twoDPeak_v1(a, rowVec, peakSet, row, col);
	// end = clock();
	// timeSpent = (double) (end - begin) / CLOCKS_PER_SEC;
	// cout << timeSpent;
	outputPeak(peakSet);
	
	// deallocate 2D matrix 
	for(int i = 0; i < row; i++) {
		delete [] a[i];
	}	
	delete [] a;		
			
	return 0;
}	

