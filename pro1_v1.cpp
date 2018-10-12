#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main() {
	int row = 1000, col = 1000;
	//int curVecSize = 10;
	vector<int> rowVec, peakSet;
	//rowVec[curVecSize] = *(new int());
	//peakSet[curVecSize] = *(new int());
	
	int** a = new int* [row];
	//a = {0};
	for(int i = 0; i < row; i++) {
		a[i] = new int[col];
	//	a[i] = {0};
	}	
	unsigned seed;
	seed = (unsigned) time(NULL);
	srand(seed);
	// generate a random 2D matrix for testing 
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			a[i][j] = rand() % 20 + 1;
//			cout << a[i][j] << " ";
//			if(j == col - 1) {
//				cout << endl;	
//			}
		}
	}
	ofstream myMatrix("matrix.data"), myPeak("final.peak");
	if(myMatrix.is_open()) {
		myMatrix << row << " " << col << endl;
		for(int i = 0; i < row; i++) {
				myMatrix << a[i][0];
			for(int j = 1; j < col; j++) {		
				myMatrix << " " << a[i][j];						
			// when the number of elements reach the mutiples of column, print to the next line			
				if(j == col - 1) {
					myMatrix << endl;	
				}						
			}
		}
//		myMatrix.close();	
	} else {
		cerr << "cannot open file.";
	}
	myMatrix.close();	
	
//	ifstream TestFile("matrix.data");
//	for(int i = 0; i < row; i++) {
//		for(int j = 0; j < col; j++) {
//			TestFile >> a[i][j];
//			cout << a[i][j] << " ";
//			if(j == col - 1) {
//				cout << endl;
//			}	
//		}		
//	} 				
			
	for(int i = 0; i < row; i++) {
		if(a[i][0] > a[i][1]) {
			rowVec.push_back(i);
			rowVec.push_back(0);
			//rowPeak.push_back(a[i][0]);
		} 	
		for(int j = 1; j < col-1; j++) {
//			if(a[i][0] > a[i][1]) {
//				rowVec.push_back(0);
//				rowVec.push_back(1);
				//rowPeak.push_back(a[i][0]);
			if((a[i][j-1] < a[i][j]) && (a[i][j] > a[i][j+1])) {
					rowVec.push_back(i);
					rowVec.push_back(j);	
			} //else if(a[i][col-1] > a[i][col-2]) {
//				rowVec.push_back(i);
//				rowVec.push_back(col-1);
				//rowPeak.push_back(a[i][col-1]);
			//}
		}
		if(a[i][col-1] > a[i][col-2]) {
			rowVec.push_back(i);
			rowVec.push_back(col-1);
			//rowPeak.push_back(a[i][col-1]);
		}								
	}
	
	for(unsigned k = 0; k < rowVec.size(); k = k+2) {
		int peakRow = rowVec[k];
		int peakCol = rowVec[k+1];
		if(peakRow == 0 && a[peakRow][peakCol] > a[peakRow+1][peakCol]) {
				peakSet.push_back(peakRow);
				peakSet.push_back(peakCol);
				peakSet.push_back(a[peakRow][peakCol]);
		} else if( (peakRow > 0 && peakRow < row-1) &&
			       (a[peakRow-1][peakCol] < a[peakRow][peakCol] && a[peakRow+1][peakCol] < a[peakRow][peakCol]) ) {
						peakSet.push_back(peakRow);
						peakSet.push_back(peakCol);
						peakSet.push_back(a[peakRow][peakCol]);						   
		} else if(peakRow == row-1 && a[peakRow][peakCol] > a[peakRow-1][peakCol]) {
				peakSet.push_back(peakRow);
				peakSet.push_back(peakCol);
				peakSet.push_back(a[peakRow][peakCol]);			
		}						
	}
	
//	for(unsigned i = 0; i < rowVec.size(); i++) {    // check
//		myMatrix << rowVec[i] << " ";
//	}
//	myMatrix << endl << endl;		
//	for(unsigned i = 0; i < peakSet.size(); i++) {   // check
//		myMatrix << peakSet[i] << " ";
//	}
								
//	myMatrix << peakSet.size();						// check
//	myMatrix << endl << endl;
	 
	unsigned peakNum = peakSet.size() / 3;
	
	if(myPeak.is_open()) {
		myPeak << peakNum << endl;
		for(unsigned i = 0; i < peakSet.size(); i = i+3) {
			myPeak << peakSet[i] << " " << peakSet[i+1] << endl;
		}
	} else {
		cerr << "cannot open file.";
	}	
	myPeak.close();
	
	for(int i = 0; i < row; i++) {
		delete [] a[i];
	}	
	delete [] a;	
	 
	return 0;
}	
