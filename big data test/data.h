#ifndef DATA_H
#define DATA_H
#include"time.h"
class data
{
private:
string timestamp;
float price;
int trade;

public:
data();
data(string, float, int);
string get_time(){ return timestamp; }
int get_trade(){ return trade; }
float get_price(){ return price; }
};

data::data(void)
{
	timestamp = "";
	price = 0;
	trade = 0;
}

data::data(std::string time, float p, int tr)
{
	timestamp = time;
	price = p;
	trade = tr;
}
#endif