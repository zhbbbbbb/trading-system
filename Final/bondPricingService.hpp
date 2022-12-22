#ifndef BOND_PRICING_SERVICE_HPP
#define BOND_PRICING_SERVICE_HPP

#include <map>
#include <vector>
#include <string>
#include "soa.hpp"
#include "pricingservice.hpp"
#include "products.hpp"


class BondPricingService : public PricingService<Bond>
{
public:
	BondPricingService();

	// Get data on our service given a key
	virtual Price<Bond>& GetData(std::string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Price<Bond>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Price<Bond>>* listener);
	
	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Price<Bond>>*>& GetListeners() const;


private:
	std::map<std::string, Price<Bond>> priceMap;
	std::vector<ServiceListener<Price<Bond>>*> listeners;
};


BondPricingService::BondPricingService() : priceMap(std::map<std::string, Price<Bond>>()), listeners(std::vector<ServiceListener<Price<Bond>>*>())
{

}

Price<Bond>& BondPricingService::GetData(std::string key)
{
	return priceMap.at(key);
}

void BondPricingService::OnMessage(Price<Bond>& data)
{// called by bondPricingerviceConnector
	std::string id = data.GetProduct().GetProductId();
	auto it = priceMap.find(id);
	if (it != priceMap.end()) // if in the map already
	{
		priceMap.erase(id);
	}
	priceMap.insert(std::pair<std::string, Price<Bond>>(id, data));

	// call ProcessAdd on all listeners
	for (auto& listener : listeners)
	{
		listener->ProcessAdd(data); // tell BondAlgoStreamingService and BondGUIService
	}
}

void BondPricingService::AddListener(ServiceListener<Price<Bond>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
const vector< ServiceListener<Price<Bond>>*>& BondPricingService::GetListeners() const
{
	return listeners;
}

#endif