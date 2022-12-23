#ifndef BONDS_HPP
#define BONDS_HPP

// contains bond information

#include <map>
#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "products.hpp"

using boost::gregorian::date;

//CUSIP     Maturity    Coupon  PV01
//91282CFX4 11/30/2024  4.500   0.01879
//91282CFW6 11/15/2025  4.500   0.02761
//91282CFZ9 11/30/2027  3.875   0.04526
//91282CFY2 11/30/2029  3.875   0.06170
//91282CFV8 11/15/2032  4.125   0.08598
//912810TM0 11/15/2042  4.000   0.14420
//912810TL2 11/15/2052  4.000   0.19917


std::map<std::string, double> CUSIP_to_PV01 = {
	{"91282CFX4", 0.01879},
	{"91282CFW6", 0.02761},
	{"91282CFZ9", 0.04526},
	{"91282CFY2", 0.06170},
	{"91282CFV8", 0.08598},
	{"912810TM0", 0.14420},
	{"912810TL2", 0.19917}
};

//string _productId, BondIdType _bondIdType, string _ticker, float _coupon, date _maturityDate
Bond bond2y("91282CFX4", CUSIP, "T", 4.500, date(2024, 11, 30));
Bond bond3y("91282CFW6", CUSIP, "T", 4.500, date(2025, 11, 15));
Bond bond5y("91282CFZ9", CUSIP, "T", 3.875, date(2027, 11, 30));
Bond bond7y("91282CFY2", CUSIP, "T", 3.875, date(2029, 11, 30));
Bond bond10y("91282CFV8", CUSIP, "T", 4.125, date(2032, 11, 15));
Bond bond20y("912810TM0", CUSIP, "T", 4.000, date(2042, 11, 15));
Bond bond30y("912810TL2", CUSIP, "T", 4.000, date(2052, 11, 15));


std::map<std::string, Bond> CUSIP_to_BOND = {
	{"91282CFX4", bond2y},
	{"91282CFW6", bond3y},
	{"91282CFZ9", bond5y},
	{"91282CFY2", bond7y},
	{"91282CFV8", bond10y},
	{"912810TM0", bond20y},
	{"912810TL2", bond30y}
};






#endif