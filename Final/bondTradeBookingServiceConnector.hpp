#ifndef BOND_TRADE_BOOKING_SERVICE_CONNECTOR_HPP
#define BOND_TRADE_BOOKING_SERVICE_CONNECTOR_HPP

#include "soa.hpp"
#include "products.hpp"
#include "bondTradeBookingService.hpp"
#include "executionservice.hpp"
#include "tradebookingservice.hpp"
#include "utility.hpp"
#include "bonds.hpp"


#include <fstream>
#include <string>
#include <iostream>
using std::string;
using std::ifstream;
using std::getline;

class BondTradeBookingServiceConnector : public Connector<Trade<Bond>>
{
public:
	// param ctor
	BondTradeBookingServiceConnector(BondTradeBookingService* _service);

	virtual void Publish(Connector<Bond>& trade);

	virtual void Subscribe(std::string filePath);

private:
	BondTradeBookingService* service;
};


// param ctor
BondTradeBookingServiceConnector::BondTradeBookingServiceConnector(BondTradeBookingService* _service) :
	service(_service)
{

}
void BondTradeBookingServiceConnector::Publish(Connector<Bond>& trade)
{

}

void BondTradeBookingServiceConnector::Subscribe(std::string filePath)
{
	ifstream file;
	string line;
	std::string CUSIP, tradeId, priceStr, book, quantityStr, sideStr;
	double price;
	long quantity;
	Side side;


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
		std::vector<std::string> info = tokenize(line, ','); //"91282CFX4,TRADE-0,99-240,TRSY2,1000000,SELL"
		CUSIP = info[0];
		tradeId = info[1];
		priceStr = info[2];
		book = info[3];
		quantityStr = info[4];
		sideStr = info[5];

		Bond product = CUSIP_to_BOND[CUSIP];
		price = StringToNum(priceStr);
		quantity = std::stoi(quantityStr);
		side = (sideStr == "BUY" ? BUY : SELL);

		Trade<Bond> trade(product, tradeId, price, book, quantity, side);
		service->OnMessage(trade);
		
	}
	file.close();
	std::cout << "Finished reading file " << filePath << endl;
}















#endif