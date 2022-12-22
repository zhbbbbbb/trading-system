#ifndef BOND_PRICING_SERVICE_CONNECTOR_HPP
#define BOND_PRICING_SERVICE_CONNECTOR_HPP

#include "bondPricingService.hpp"
#include "pricingservice.hpp"
#include "products.hpp"
#include "soa.hpp"
#include "utility.hpp"
#include "bonds.hpp"

#include <fstream>
#include <string>
#include <iostream>
using std::string;
using std::ifstream;
using std::getline;


// get data from txt file and then tell BondPricingService
class BondPricingServiceConnector : public Connector<Price<Bond>>
{
public:
	// param ctor
	BondPricingServiceConnector(BondPricingService* _service);

	virtual void Publish(Price<Bond>& price);

	virtual void Subscribe(std::string filePath);

private:
	BondPricingService* service;
};


BondPricingServiceConnector::BondPricingServiceConnector(BondPricingService* _service):
	service(_service)
{

}

void BondPricingServiceConnector::Publish(Price<Bond>& price)
{

}

void BondPricingServiceConnector::Subscribe(std::string filePath)
{
	ifstream file;
	string line;
	std::string CUSIP, priceMidStr, spreadStr;
	double priceMid, spread;
	std::vector<std::string> info;

	//read file
	file.open(filePath);
	if (!file)
	{
		std::cerr << "Error: file cannot be opened." << std::endl;
	}

	while (!file.eof())
	{
		file >> line; // sets EOF flag if no value found
		//cout << line << endl;
		info = tokenize(line, ','); //"{CUSIP},{to_string(digitsMid)},{to_string(digitsSpread)}\n"
		CUSIP = info[0];
		priceMidStr = info[1];
		spreadStr = info[2];

		Bond product = CUSIP_to_BOND[CUSIP];
		priceMid = StringToNum(priceMidStr);
		spread = StringToNum(spreadStr);

		Price<Bond> price(product, priceMid, spread);

		service->OnMessage(price); // tell BondPricingService

	}
	file.close();
	std::cout << "Finished reading file " << filePath << endl;
}













#endif