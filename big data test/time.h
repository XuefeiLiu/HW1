#ifndef TIME_H
#define TIME_H
#include <iostream>
#include <boost/date_time.hpp>
#include "boost/date_time/posix_time/posix_time.hpp" 
namespace bt = boost::posix_time;
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::local_time;
using namespace std;

std::time_t pt_to_time_t(const bt::ptime& pt)
{
	bt::time_duration td = hours(0) + microseconds(0);
	bt::ptime timet_start(boost::gregorian::date(1970, 1, 1), td);
	bt::time_duration diff = pt - timet_start;
	return diff.ticks() / (bt::time_duration::rep_type::ticks_per_second / 1000000);

}
std::time_t microseconds_from_epoch(const std::string& s)
{

	istringstream is(s);
	local_time_input_facet* input_facet = new time_input_facet();
	is.imbue(locale(is.getloc(), input_facet));
	input_facet->format("%Y%m%d:%H:%M:%S%F");
	ptime ldt(not_a_date_time);
	is >> ldt;
	return pt_to_time_t(ldt);
}

#endif