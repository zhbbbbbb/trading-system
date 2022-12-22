#ifndef BOND_INQUIRY_SERVICE_HPP
#define BOND_INQUIRY_SERVICE_HPP

// define BondInquiryService and BondInquiryServiceConnector in one file because they contain pointers to each other.

#include "soa.hpp"
#include "products.hpp"
#include "tradebookingservice.hpp"
#include "inquiryservice.hpp"
#include "utility.hpp"
#include "bonds.hpp"


#include <string>
#include <vector>
#include <map>

#include <fstream>
using std::string;
using std::ifstream;
using std::getline;

class BondInquiryServiceConnector;

class BondInquiryService : public InquiryService<Bond>
{
public:
	BondInquiryService();

	// Get data on our service given a key
	virtual Inquiry<Bond>& GetData(std::string key);

	virtual BondInquiryServiceConnector& GetConnector() const;

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Inquiry<Bond>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Inquiry<Bond>>* listener);

	// Get all listeners on the Service.
	virtual const std::vector<ServiceListener<Inquiry<Bond>>*>& GetListeners() const;

	// Send a quote back to the client
	virtual void SendQuote(const string& inquiryId, double price);

	// Reject an inquiry from the client
	virtual void RejectInquiry(const string& inquiryId);


private:
	std::map<std::string, Inquiry<Bond>> inquiryMap;
	std::vector<ServiceListener<Inquiry<Bond>>*> listeners;
	BondInquiryServiceConnector* connector;
};

class BondInquiryServiceConnector : public Connector<Inquiry<Bond>>
{
public:
	// param ctor
	BondInquiryServiceConnector(BondInquiryService* _service);

	virtual void Publish(Inquiry<Bond>& inquiry);

	virtual void Subscribe(std::string filePath);

private:
	BondInquiryService* service;
};

BondInquiryService::BondInquiryService():
	inquiryMap(std::map<std::string, Inquiry<Bond>>()), listeners(std::vector<ServiceListener<Inquiry<Bond>>*>()), connector(new BondInquiryServiceConnector(this))
{

}

// Get data on our service given a key
Inquiry<Bond>& BondInquiryService::GetData(std::string key)
{
	return inquiryMap.at(key);
}

BondInquiryServiceConnector& BondInquiryService::GetConnector() const
{
	return *connector;
}

// The callback that a Connector should invoke for any new or updated data
void BondInquiryService::OnMessage(Inquiry<Bond>& data)
{
	std::string id = data.GetInquiryId(); // inquiry id not product id
	auto it = inquiryMap.find(id);
	if (it != inquiryMap.end())
	{
		inquiryMap.erase(id);
	}
	inquiryMap.insert(std::pair<std::string, Inquiry<Bond>>(id, data));

	switch (data.GetState())
	{
	case RECEIVED:
		// send a quote of 100 back to connector
		data.SetPrice(100.0);
		connector->Publish(data); // send the quote back to connector
		// when the inquiry has RECEIVED state, tell listeners
		for (auto& listener : listeners)
		{
			listener->ProcessAdd(data);
		}
		break;
	case QUOTED:
		data.SetState(DONE); // change state from quoted to done
		break;
	default:
		break;
	}

	
}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
void BondInquiryService::AddListener(ServiceListener<Inquiry<Bond>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
const std::vector<ServiceListener<Inquiry<Bond>>*>& BondInquiryService::GetListeners() const
{
	return listeners;
}


// Send a quote back to the client
void BondInquiryService::SendQuote(const string& inquiryId, double price)
{
	auto it = inquiryMap.find(inquiryId);
	if (it == inquiryMap.end()) return; // if not in map then do nothing
	it->second.SetPrice(price); // update price

	// tell listeners
	for (auto& listener : listeners)
	{
		listener->ProcessAdd(it->second);
	}
}

// Reject an inquiry from the client
void BondInquiryService::RejectInquiry(const string& inquiryId)
{
	auto it = inquiryMap.find(inquiryId);
	if (it == inquiryMap.end()) return; // if not in map then do nothing
	it->second.SetState(REJECTED); // reject inquiry

	// tell listeners
	for (auto& listener : listeners)
	{
		listener->ProcessAdd(it->second);
	}
}


BondInquiryServiceConnector::BondInquiryServiceConnector(BondInquiryService* _service) :
	service(_service)
{

}

void BondInquiryServiceConnector::Publish(Inquiry<Bond>& inquiry)
{
	// received the quote from BondInquiryService
	inquiry.SetState(QUOTED);
	service->OnMessage(inquiry);
}


void BondInquiryServiceConnector::Subscribe(std::string filePath)
{// read from inquiries.txt
	ifstream file;
	string line;
	std::string inquiryId, CUSIP, sideStr, quantityStr, priceStr, inquiryStateStr;
	Side side;
	double price;
	long quantity;
	InquiryState inquiryState;
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
		info = tokenize(line, ','); //"{inquiryId},{CUSIP},{side},{quantity},{to_string(digitsInquiry)},{inquiryState}\n"
		inquiryId = info[0];
		CUSIP = info[1];
		sideStr = info[2];
		quantityStr = info[3];
		priceStr = info[4];
		inquiryStateStr = info[5];

		Bond product = CUSIP_to_BOND[CUSIP];
		side = (sideStr == "BUY" ? BUY : SELL);
		quantity = std::stoi(quantityStr);
		price = StringToNum(priceStr);
		// RECEIVED, QUOTED, DONE, REJECTED, CUSTOMER_REJECTED
		if (inquiryStateStr == "RECEIVED")
		{
			inquiryState = RECEIVED;
		}
		else if (inquiryStateStr == "QUOTED")
		{
			inquiryState = QUOTED;
		}
		else if (inquiryStateStr == "DONE")
		{
			inquiryState = DONE;
		}
		else if (inquiryStateStr == "REJECTED")
		{
			inquiryState = REJECTED;
		}
		else if (inquiryStateStr == "CUSTOMER_REJECTED")
		{
			inquiryState = CUSTOMER_REJECTED;
		}
		else
		{
			std::cerr << "Invalid Inquiry State" << std::endl;
		}

		// create inquiry
		Inquiry<Bond> inquiry(inquiryId, product, side, quantity, price, inquiryState);

		service->OnMessage(inquiry); // tell BondPricingService

	}
	file.close();
	cout << "Finished reading file " << filePath << endl;
}




#endif