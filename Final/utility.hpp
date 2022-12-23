#ifndef UTILITY_HPP
#define UTILITY_HPP

// utility functions for the project

#include "executionservice.hpp"
#include "pricingservice.hpp"
#include "tradebookingservice.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "boost/date_time/posix_time/posix_time.hpp"
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::posix_time::microsec_clock;



template <typename T>
std::ostream& operator << (std::ostream& os, std::vector<T>& vec)
{
	for (unsigned int i = 0; i < vec.size(); ++i)
	{
		os << vec[i] << " ";
	}
	return os;
}

// tokenize a line into a vector of words
std::vector<std::string> tokenize(const std::string& text, const char& delim)
{
	std::vector<std::string> vec;
	std::istringstream input;
	input.str(text);
	for (std::string line; std::getline(input, line, delim); )
	{
		vec.push_back(line);
	}
	return vec;
}

double StringToNum(const std::string& priceString)
{
	std::vector<std::string> vecDigits = tokenize(priceString, '-');
	double integer = std::stoi(vecDigits[0]);
	double digits12 = std::stoi(vecDigits[1].substr(0, 2));
	double digits3 = std::stoi(vecDigits[1].substr(2,3));
	double price = integer + digits12 / 32.0 + digits3 / 256.0;
	return price;
}


//// the following are defined in their original files

//enum OrderType { FOK, IOC, MARKET, LIMIT, STOP };
//enum Market { BROKERTEC, ESPEED, CME };
//enum ProductType { IRSWAP, BOND };
//enum DayCountConvention { THIRTY_THREE_SIXTY, ACT_THREE_SIXTY };
//enum PaymentFrequency { QUARTERLY, SEMI_ANNUAL, ANNUAL };
//enum FloatingIndex { LIBOR, EURIBOR };
//enum FloatingIndexTenor { TENOR_1M, TENOR_3M, TENOR_6M, TENOR_12M };
//enum Currency { USD, EUR, GBP };
//enum SwapType { STANDARD, FORWARD, IMM, MAC, BASIS };
//enum SwapLegType { OUTRIGHT, CURVE, FLY };
//enum BondIdType { CUSIP, ISIN };
//enum InquiryState { RECEIVED, QUOTED, DONE, REJECTED, CUSTOMER_REJECTED };
//enum Market { BROKERTEC, ESPEED, CME };
//enum PricingSide { BID, OFFER };


//std::string OrderTypeToString(OrderType orderType)
//{
//	std::string result;
//	switch (orderType)
//	{
//	case FOK:
//		result = "FOK"; break;
//	case IOC:
//		result = "IOC"; break;
//	case MARKET:
//		result = "MARKET"; break;
//	case LIMIT:
//		result = "LIMIT"; break;
//	case STOP:
//		result = "STOP"; break;
//	default:
//		result = ""; break;
//	}
//	return result;
//}

//std::string PricingSideToString(PricingSide pricingSide)
//{
//	std::string result;
//	switch (pricingSide)
//	{
//	case BID:
//		result = "BID"; break;
//	case OFFER:
//		result = "OFFER"; break;
//	default:
//		result = ""; break;
//	}
//	return result;
//}

//std::string SideToString(Side side)
//{
//	std::string result;
//	switch (side)
//	{
//	case BUY:
//		result = "BUY"; break;
//	case SELL:
//		result = "SELL"; break;
//	default:
//		result = ""; break;
//	}
//	return result;
//}





#endif