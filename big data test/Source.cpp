#include"read file.h"
#include <climits>
#include <iostream>
#include <chrono>
#include <fstream>
#include"scrub.h"
#include"write file.h"
#include"Normal.h"

//This program uses 10 threads to read data from file and store the data in 10 vectors of user defined type data.
//Then we combine the 10 vectore into a single one to store it in memory.
//The standard to pick noise is to detect whether price and volume is negative or beyond three standard deviations.
//We use user defined function to transform date to a number and then sort the vector according to this number
//Finally we get the return of price and can do the normality test.
//However, it took so much time to sort data to do the normality test. Hopefully I can get more time to finish it.



int main (int argc, const char* argv[]) 
{

	// Minimal error checking.
	if (argc != 2) {
		cout << "Must specify a file name!" << endl;
		cout << "Invoke like this: FileSize <file name>" << endl;
		exit(1);
	}
	string filename = argv[1];
	
	vector<data> vec;
	vec=input(filename);
	output(vec);
	return 0;
}