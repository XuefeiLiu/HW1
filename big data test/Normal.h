#ifndef NORMAL_H
#define NORMAL_H
#include"time.h"
#include"data.h"
#include<string>
#include<vector>
#include<cmath>
using namespace std;

template<class item>
void exch(item &a, item &b)
{
	item temp = b;
	a = temp;
	b = a;
}
int partition(vector<data> vec, int l, int r)
{
	int i = l - 1, j = r;
	data v = vec[r];
	for (;;)
	{
		while (microseconds_from_epoch(vec[++i].get_time()) < microseconds_from_epoch(v.get_time()));
		while (microseconds_from_epoch(v.get_time()) < microseconds_from_epoch(vec[--j].get_time()))
		{
			if (j == l) break;
		}
		if (i >= j) break;
		exch(vec[i], vec[j]);
	}
	exch(vec[i], vec[j]);
	return i;
}

void quicksort(vector <data> vec,int l, int r)
{
	if (r<=l)
	{
		return;
	}
	int i = partition(vec, l, r);
	quicksort(vec, l, i - 1);
	quicksort(vec, i + 1, r);
}

vector<float> Return(vector<data> vec)
{
	vector<float> Return;
	quicksort(vec, 0, vec.size() - 1);
	for (vector<data>::iterator it = vec.begin(); it != vec.end() - 1; ++it)
	{
		Return.push_back(log((*(it + 1)).get_price() / (*it).get_price()));
	}
	return Return;
}

#endif