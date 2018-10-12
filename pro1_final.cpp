#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

void twoDPeak(int**, vector<int>&, vector<int>&, int, int);

int main(int argc, char* argv[]) {
	// clock begin
	srand(time(NULL));
	clock_t begin, end;
	double timeSpent;
	begin = clock();	
	
	int row, col;
	
	// set input pathway
	char inputPath[20];
	// copy argv[1] to inputPath
	strcpy(inputPath, argv[1]);
	// connect inputPath to /matrix.data
	strcat(inputPath, "/matrix.data");
	cout << "input "<< inputPath << endl;  // for check
	ifstream input(inputPath);   

	if(input.is_open()) {
		// set the value of row and col from input file
		input >> row;
		input >> col;
		cout << row << " " << col << endl;   // for check
	} else {
		cerr << "cannot open file";
	}
	if(argc < 2) {
		cout << "missing argumant" << endl;
		exit(0);
	}		
	// create a 2D matrix by allocating dynamic array
	int** a = new int* [row];	
	for(int i = 0; i < row; i++) {
		a[i] = new int[col];
	}

	// input the rest of elements into 2D array
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			input >> a[i][j];
		}	
	}
	input.close();	 
	
	vector<int> rowVec, peakSet;
	// peak finder
	twoDPeak(a, rowVec, peakSet, row, col);
	
	unsigned peakNum = peakSet.size() / 3;
	
	// set output pathway
	char outputPath[20]; 
	strcpy(outputPath, argv[1]); 
	strcat(outputPath, "/final.peak");
	cout << "output " << outputPath << endl;  // for check
	ofstream output(outputPath);

	if(output.is_open()) {
		output << peakNum << endl;
		// output (row, col) of local maximums, without their value (the index of peakSet which are multiple of 2 will be ignored)	
		for(unsigned i = 0; i < peakSet.size(); i = i+3) {
			output <<peakSet[i] << " " << peakSet[i+1] << endl;
		}
	} else {
		cerr << "cannot open file " << endl;	
	}	
	
	output.close();	
	
	// deallocate 2D matrix 
	for(int i = 0; i < row; i++) {
		delete [] a[i];
	}	
	delete [] a;
	
	// clock end
	end = clock();
	timeSpent = (double) (end - begin) / CLOCKS_PER_SEC;
	cout << timeSpent << endl;		
			
	return 0;
}	

void twoDPeak(int** a, vector<int>& vec1, vector<int>& vec2, int row, int col) {     // O(N^2)
	// compare every element in each row
	for(int i = 0; i < row; i++) {                                          		 // O(N)
		// for bondary cases (i,0), larger elements are stored in vector
		if(a[i][0] >= a[i][1]) {
			vec1.push_back(i);
			vec1.push_back(0);
		} 
		// for other elements except bondary elements, larger elements are stored in vector	
		for(int j = 1; j < col-1; j++) {                                     		 // O(N)
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
	
	for(unsigned k = 0; k < vec1.size(); k = k+2) {								    // O(N)
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

