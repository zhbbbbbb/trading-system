#ifndef BOND_MARKET_DATA_SERVICE_CONNECTOR_HPP
#define BOND_MARKET_DATA_SERVICE_CONNECTOR_HPP


#include "bondMarketDataService.hpp"
#include "products.hpp"
#include "soa.hpp"
#include "utility.hpp"

#include <fstream>
#include <string>
#include <iostream>
using std::string;
using std::ifstream;
using std::getline;

class BondMarketDataServiceConnector : public Connector<OrderBook<Bond>>
{
public:
	// param ctor
	BondMarketDataServiceConnector(BondMarketDataService* _service);

	virtual void Publish(OrderBook<Bond>& orderBook);

	virtual void Subscribe(std::string filePath);

private:
	BondMarketDataService* service;
};


// param ctor
BondMarketDataServiceConnector::BondMarketDataServiceConnector(BondMarketDataService* _service) : service(_service)
{

}
void BondMarketDataServiceConnector::Publish(OrderBook<Bond>& orderBook)
{

}

void BondMarketDataServiceConnector::Subscribe(std::string filePath)
{
	ifstream file;
	string line;
	std::string CUSIP, priceStr, quantityStr, pricingSideStr;
	std::vector<Order> bidStack, offerStack;
	std::vector<std::string> info;
	double price;
	long quantity;
	PricingSide pricingSide;
	int count;
	count = 0;


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
		info = tokenize(line, ','); //"{CUSIP},{to_string(digitsBid)},{quantity},BID\n"
		priceStr = info[1];
		quantityStr = info[2];
		pricingSideStr = info[3];

		

		price = StringToNum(priceStr);
		quantity = std::stoi(quantityStr);
		pricingSide = (pricingSideStr == "BID" ? BID : OFFER);
		
		Order order(price, quantity, pricingSide);

		// push order to the corresponding order stack
		if (pricingSide==BID)
		{
			bidStack.push_back(order);
		}
		else
		{
			offerStack.push_back(order);
		}
		count += 1; // increment count

		if (!(count % 10))
		{// for every 10 lines, create a orderBook
			CUSIP = info[0];
			Bond bond = CUSIP_to_BOND[CUSIP];
			// construct orderbook
			OrderBook<Bond> orderBook(bond, bidStack,offerStack);
			bidStack.clear();
			offerStack.clear();
			service->OnMessage(orderBook);
			count %= 10; // keep count small
		}
	}
	file.close();
	std::cout << "Finished reading file " << filePath << endl;
}









#endif