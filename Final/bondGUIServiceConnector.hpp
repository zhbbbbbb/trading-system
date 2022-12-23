#ifndef BOND_GUI_SERVICE_CONNECTOR_HPP
#define BOND_GUI_SERVICE_CONNECTOR_HPP


#include "pricingservice.hpp"
#include "products.hpp"
#include "soa.hpp"
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "boost/date_time/posix_time/posix_time.hpp"
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::posix_time::microsec_clock;
using boost::posix_time::millisec;



class BondGUIServiceConnector : public Connector<Price<Bond>>
{
public:

	virtual void Publish(Price<Bond>& price);
	virtual void Publish(Price<Bond>& price, ptime time);

	virtual void Subscribe(std::string filePath);

private:
	static std::string outputFilePath;
	static bool rewrite;
};

std::string BondGUIServiceConnector::outputFilePath = "gui.txt";
bool BondGUIServiceConnector::rewrite = false; // rewrite files

void BondGUIServiceConnector::Publish(Price<Bond>& price)
{

}

// publish with given time
void BondGUIServiceConnector::Publish(Price<Bond>& price, ptime time)
{//publish Price from bondGUIServiceListener to gui.txt
	ptime now = microsec_clock::local_time();
	Bond product = price.GetProduct();
	std::string id = product.GetProductId();
	double midPrice = price.GetMid();
	double spread = price.GetBidOfferSpread();

	// write to local txt file
	std::ofstream file;
	if (rewrite)
	{// rewrite file
		file.open(outputFilePath);
		file << now << "," << id << "," << midPrice << "," << spread << endl;
	}
	else
	{// append to original text
		file = std::ofstream(outputFilePath, std::ofstream::out | std::ofstream::app);
		file << now << "," << id << "," << midPrice << "," << spread << endl;
	}
	file.close();
}

void BondGUIServiceConnector::Subscribe(std::string filePath)
{

}







#endif