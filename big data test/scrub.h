#ifndef SCRUB_H
#define SCRUB_H
#include"data.h"
#include<vector>
#include <boost/tuple/tuple.hpp>
#include <numeric>
using namespace std;

boost::tuple <vector<data>, vector<data>> scrub(vector<data> vec)
{
	std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();
	vector<data> vec1;
	vector<data> vec2;
	vector<float> vec3;
	vector<int> vec4;
	for (vector<data>::iterator it = vec.begin(); it != vec.end(); ++it)
	{

		vec3.push_back((*it).get_price());
		vec4.push_back((*it).get_trade());
		
	}
	float sum_price = accumulate(vec3.begin(), vec3.end(), 0.0);
	float mean_price = sum_price / vec3.size();

	float sq_sum_price = inner_product(vec3.begin(), vec3.end(), vec3.begin(), 0.0);
	float stdev_price = std::sqrt(sq_sum_price / vec3.size() - mean_price * mean_price);
	
	float sum_trade = accumulate(vec4.begin(), vec4.end(), 0.0);
	float mean_trade = sum_trade / vec4.size();
	float sq_sum_trade = inner_product(vec4.begin(), vec4.end(), vec4.begin(), 0.0);
	float stdev_trade = std::sqrt(sq_sum_trade / vec4.size() - mean_trade * mean_trade);
	
	
	for (vector<data>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if ((*it).get_price() > mean_price + 3 * stdev_price || (*it).get_price() <  mean_price - 3*stdev_price || (*it).get_price()<0)
			vec2.push_back(*it);
		else if ((*it).get_trade() > mean_trade + 3 * stdev_trade || (*it).get_trade() <  mean_trade - 3*stdev_trade || (*it).get_trade()<0)
			vec2.push_back(*it);
		else
			vec1.push_back(*it);
		
	}
	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
	std::cout << "cumulative time to scrub is"
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
		<< " milliseconds\n";

	return boost::make_tuple(vec1, vec2);
}


#endif