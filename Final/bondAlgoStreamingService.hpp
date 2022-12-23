#ifndef BOND_ALGO_STREAMING_SERVICE_HPP
#define BOND_ALGO_STREAMING_SERVICE_HPP

#include "soa.hpp"
#include "streamingservice.hpp"
#include "products.hpp"

#include <vector>
#include <map>
#include <string>

class BondAlgoStreamingService : public AlgoStreamingService<Bond>
{
public:
	BondAlgoStreamingService();

	// Get data on our service given a key
	virtual AlgoStream<Bond>& GetData(std::string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(AlgoStream<Bond>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<AlgoStream<Bond>>* listener);

	// Get all listeners on the Service.
	virtual const vector<ServiceListener<AlgoStream<Bond>>*>& GetListeners() const;

	// when listener gets a new Price
	virtual void AddPrice(const Price<Bond>& price);

private:
	std::map<std::string, AlgoStream<Bond>> algostreamMap;
	std::vector<ServiceListener<AlgoStream<Bond>>*> listeners;
};


BondAlgoStreamingService::BondAlgoStreamingService() : algostreamMap(std::map<std::string, AlgoStream<Bond>>()), listeners(std::vector<ServiceListener<AlgoStream<Bond>>*>())
{

}

// Get data on our service given a key
AlgoStream<Bond>& BondAlgoStreamingService::GetData(std::string key)
{
	return algostreamMap.at(key);
}

// The callback that a Connector should invoke for any new or updated data
void BondAlgoStreamingService::OnMessage(AlgoStream<Bond>& data)
{

}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
void BondAlgoStreamingService::AddListener(ServiceListener<AlgoStream<Bond>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
const vector< ServiceListener<AlgoStream<Bond>>*>& BondAlgoStreamingService::GetListeners() const
{
	return listeners;
}

void BondAlgoStreamingService::AddPrice(const Price<Bond>& price)
{
	Bond product = price.GetProduct();
	std::string id = product.GetProductId();
	auto it = algostreamMap.find(id);
	if (it != algostreamMap.end())
	{
		algostreamMap.erase(id);
	}
	//create a new
	PriceStream<Bond> priceStream(product, PriceStreamOrder(-99.0, 0, 0, BID), PriceStreamOrder(-99.0, 0, 0, OFFER));
	AlgoStream<Bond> algoStream(priceStream);
	algoStream.UpdatePriceStream(price);
	algostreamMap.insert(std::pair<std::string, AlgoStream<Bond>>(id, algoStream));

	for (auto& listener : listeners)
	{
		listener->ProcessAdd(algoStream); // tell BondStreamingServiceListener
	}

}



#endif