#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

void createMatrix(int** a, int row, int col) {
	unsigned seed;
	seed = (unsigned) time(NULL);
	srand(seed);
	// generate a random 2D matrix 
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			a[i][j] = rand() % 20 + 1;
			//cout << a[i][j] << " ";
		}
	}
}	
void createMatriFile(int** a, int row, int col) {
	// output the above matrix to a new file which is created at the same time
	ofstream outputMatrix("matrixName.data");
	if(outputMatrix.is_open()) {
		outputMatrix << row << " " << col << endl;
		for(int i = 0; i < row; i++) {
				outputMatrix << a[i][0];
			for(int j = 1; j < col; j++) {		
				outputMatrix << " " << a[i][j];						
			// when the number of elements reach the end of column size, output to the next line			
				if(j == col - 1) {
					outputMatrix << endl;	
				}						
			}
		}
	} else {
		cerr << "cannot open file.";
	}
	outputMatrix.close();	
}	

void readMatriFile(ifstream& input, int**a, int row, int col) {
	//ifstream input("TA_matrix_1.data");
	//if(input.is_open()) {
		//int dum1, dum2;
		//input >> dum1;
		//input >> dum2;
		for(int i = 0; i < row; i++) {
			for(int j = 0; j < col; j++) {
				input >> a[i][j];
			}		
		} 
	//} else {
	//	cerr << "cannot open file.";
	//}
	input.close();				
}
	
void twoDPeak_v1(int** a, vector<int>& vec1, vector<int>& vec2, int row, int col) {  // O(N^2)
	// compare every element in each row
	for(int i = 0; i < row; i++) {                                           // O(N)
		// for bondary cases (i,0), larger elements are stored in vector
		if(a[i][0] >= a[i][1]) {
			vec1.push_back(i);
			vec1.push_back(0);
		} 
		// for other elements except bondary elements, larger elements are stored in vector	
		for(int j = 1; j < col-1; j++) {                                     // O(N)
			if((a[i][j-1] <= a[i][j]) && (a[i][j] >= a[i][j+1])) {
					vec1.push_back(i);
					vec1.push_back(j);	
			} 
		}
		// for bondary cases (i,col-1), larger elements are stored in vect1
		if(a[i][col-1] >= a[i][col-2]) {
			vec1.push_back(i);
			vec1.push_back(col-1);
		}								
	}	
	
	for(unsigned k = 0; k < vec1.size(); k = k+2) {							// O(N)
		// compare larger elements stored in vec1 with other elements within their own columns
		// get info of larger elements from vec1
		int peakRow = vec1[k];
		int peakCol = vec1[k+1];
		// for bondary cases (0, col), larger elements are stored in vec2, considered as local maximums
		if(peakRow == 0 && a[peakRow][peakCol] >= a[peakRow+1][peakCol]) {
				vec2.push_back(peakRow);
				vec2.push_back(peakCol);
				vec2.push_back(a[peakRow][peakCol]);
		// for other elements except bondary elements, larger elements are stored in vec2	
		} else if( (peakRow > 0 && peakRow < row-1) &&
			       (a[peakRow-1][peakCol] <= a[peakRow][peakCol] && a[peakRow+1][peakCol] <= a[peakRow][peakCol]) ) {
						vec2.push_back(peakRow);
						vec2.push_back(peakCol);
						vec2.push_back(a[peakRow][peakCol]);	
		// for bondary cases (row-1, col), larger elements are stored in vec2, considered as local maximums 									   
		} else if(peakRow == row-1 && a[peakRow][peakCol] >= a[peakRow-1][peakCol]) {
				vec2.push_back(peakRow);
				vec2.push_back(peakCol);
				vec2.push_back(a[peakRow][peakCol]);			
		}						
	}
		
}
	
void outputPeak(vector<int>& vec) {
	unsigned peakNum = vec.size() / 3;
	ofstream outputPeak("test.peak");
	
	if(outputPeak.is_open()) {
		outputPeak << peakNum << endl;
		// output (row, col) of local maximums, without their value (the index of vec2 which are multiple of 2 will be ignored)	
		for(unsigned i = 0; i < vec.size(); i = i+3) {
			outputPeak <<vec[i] << " " << vec[i+1] << endl;
		}
	} else {
		cerr << "cannot open file.";
	}	
	outputPeak.close();	
}	


