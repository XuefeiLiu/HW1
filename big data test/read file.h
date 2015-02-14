#include <iostream>   
#include <string>   
#include<fstream>   
#include<vector>
#include"data.h"
#include<assert.h>
#include <boost/thread.hpp>
#include <random>
#include<algorithm>
#include <climits>
#include <iostream>
#include <chrono>


using namespace std;
static const int NUM_THREADS = 10;
stringstream file;
std::vector<data> VECTOR[NUM_THREADS];
std::vector<data> Merge;

stringstream cut(string filename,int i)
{

	fstream in(filename);
	stringstream out;
	//assert(in);
	in.seekg(0, in.end);
	int length = in.tellg();
	streampos sp = in.tellg();
	in.seekg(i*sp / NUM_THREADS, in.beg);
	long size = length / NUM_THREADS;
	char* buffer = new char[size];
	
	in.read(buffer, size);
	out.write(buffer, size);
	string value;
	delete[] buffer;
	in.close();
	return out;

}





std::vector<data> read(stringstream &file)
{
	
	string value;
	std::vector<data> vec;
	int i = 1;
	string t;
	float price;
	int trade;
	getline(file, value, '\n');
	while (file.good())
	{
		switch (i){
		case (1) :
		{
					 getline(file, value, ',');
					 t = value;
					 i = 2;
					 break;
		}

		case (2) :
		{
					 getline(file, value, ',');
					 price = stof(value);
					 i = 3;
					 break;
		}
		case(3) :
		{
					getline(file, value, '\n');
					trade = stoi(value);
					vec.push_back(data(t, price, trade));
					i = 1;
					break;
		}
		}


	}
	return vec;
}

void ThreadFunction(string filename, int threadID) {
	stringstream file = cut(filename, threadID);
	vector<data> vec = read(file);
	VECTOR[threadID] = vec;

}

vector<data> input(string filename)
{
	std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();
	boost::thread threads[NUM_THREADS];
	
	for (int i = 0; i < NUM_THREADS; ++i) {
		threads[i]=boost::thread (ThreadFunction, filename, i);
	}
	
	for (int i = 0; i < NUM_THREADS; ++i) {
		threads[i].join();
		Merge.insert(Merge.end(), VECTOR[i].begin(), VECTOR[i].end());
	
	}
	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
	
	std::cout << "read 'data.txt' uses"
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
		<< " milliseconds\n";
	return Merge;
}