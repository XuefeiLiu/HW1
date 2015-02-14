#ifndef WRITE_FILE_H
#define WRITE_FILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include"data.h"

using namespace std;
void write(char* fileName,vector <data> vec) 
{
	ofstream fout(fileName);
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int j = 0; j < 1; j++)
		{

			fout << vec[i].get_time() << ",";
			fout << vec[i].get_price() << ",";
			fout << vec[i].get_price() << "\n";
		}
	}
		
		fout.close();
}
void output(vector<data> vec)
{

	vector<data> vec1 = scrub(vec).get<0>();
	std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();
	write("singal.txt", vec1);
	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();

	std::cout << "output 'singal.txt' uses"
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
		<< " milliseconds\n";

	vector<data> vec2 = scrub(vec).get<1>();
	std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
	write("noise.txt", vec2);
	std::chrono::system_clock::time_point t3 = std::chrono::system_clock::now();

	std::cout << "output 'noise.txt' uses"
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count()
		<< " milliseconds\n";
}
#endif