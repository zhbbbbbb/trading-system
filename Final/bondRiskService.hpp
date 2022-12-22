#ifndef BOND_RISK_SERVICE_HPP
#define BOND_RISK_SERVICE_HPP

#include "riskservice.hpp"
#include "products.hpp"
#include "bondpositionservice.hpp"
#include <map>
#include <vector>
#include <string>
#include "bonds.hpp"

//template<typename T>
//class RiskService : public Service<string, PV01 <T> >
//{
//
//public:
//
//    // Add a position that the service will risk
//    void AddPosition(Position<T>& position) = 0;
//
//    // Get the bucketed risk for the bucket sector
//    const PV01< BucketedSector<T> >& GetBucketedRisk(const BucketedSector<T>& sector) const = 0;
//
//};



class BondRiskService : public RiskService<Bond>
{
public:
	BondRiskService();

	// Get data on our service given a key
	virtual PV01<Bond>& GetData(std::string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PV01<Bond>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<PV01<Bond>>* listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<PV01<Bond>>*>& GetListeners() const;

	// Add a position that the service will risk
	virtual void AddPosition(Position<Bond>& position);

	// Get the bucketed risk for the bucket sector
	virtual const PV01<BucketedSector<Bond>> GetBucketedRisk(const BucketedSector<Bond>& sector) const;

private:
	std::map<std::string, PV01<Bond>> riskMap;
	std::vector<ServiceListener<PV01<Bond>>*> listeners;
};


BondRiskService::BondRiskService() : riskMap(std::map<std::string, PV01<Bond>>()), listeners(std::vector<ServiceListener<PV01<Bond>>*>())
{

}

PV01<Bond>& BondRiskService::GetData(std::string key)
{
	return riskMap.at(key);
}

void BondRiskService::OnMessage(PV01<Bond>& data)
{
	// does not need a connector
}

void BondRiskService::AddListener(ServiceListener<PV01<Bond>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
const vector<ServiceListener<PV01<Bond>>*>& BondRiskService::GetListeners() const
{
	return listeners;
}


void BondRiskService::AddPosition(Position<Bond>& position)
{
	string id = position.GetProduct().GetProductId();
	long quantity = position.GetAggregatePosition();
	auto it = riskMap.find(id);
	if (it != riskMap.end())
	{// if already in 
		it->second.AddQuantity(quantity);
	}
	else
	{// if not already in riskMap
		Bond product = position.GetProduct();
		riskMap.insert(std::pair<std::string, PV01<Bond>>(id, PV01<Bond>(product, CUSIP_to_PV01[id], quantity)));
	}

	it = riskMap.find(id);
	// call ProcessAdd on all listeners
	for (auto& listener : listeners)
	{
		listener->ProcessAdd(it->second);
	}
}

// Get the bucketed risk for the bucket sector
const PV01<BucketedSector<Bond>> BondRiskService::GetBucketedRisk(const BucketedSector<Bond>& sector) const
{
	double pv01;
	long quantity;
	double pv01Total = 0;
	long quantityTotal = 0;
	std::string id;
	for (const auto& product : sector.GetProducts())
	{
		id = product.GetProductId();
		auto it = riskMap.find(id);
		if (it != riskMap.end())
		{// if the product is in the riskMap
			pv01 = it->second.GetPV01();
			quantity = it->second.GetQuantity();
			pv01Total += pv01 * ((double) quantity);
			quantityTotal += quantity;
		}
	}
	if (quantityTotal != 0)
	{
		pv01Total /= ((double) quantityTotal); // PV01Total is the quantity-weighted average PV01
	}
	return PV01<BucketedSector<Bond>>(sector, pv01Total, quantityTotal);
}





#endif