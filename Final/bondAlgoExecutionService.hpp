#ifndef	BOND_ALGO_EXECUTION_SERVICE_HPP
#define BOND_ALGO_EXECUTION_SERVICE_HPP

#include "soa.hpp"
#include "executionservice.hpp"
#include "products.hpp"
#include <vector>
#include <map>
#include <string>


class BondAlgoExecutionService : public AlgoExecutionService<Bond>
{
public:
	BondAlgoExecutionService();

	// Get data on our service given a key
	virtual AlgoExecution<Bond>& GetData(std::string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(AlgoExecution<Bond>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<AlgoExecution<Bond>>* listener);

	// Get all listeners on the Service.
	virtual const std::vector< ServiceListener<AlgoExecution<Bond>>*>& GetListeners() const;

	// check if algo wants to send order
	virtual bool GoodToSend(const OrderBook<Bond>& orderBook);

	// update execution order when given an order book
	virtual void AddOrderBook(const OrderBook<Bond>& orderBook);

private:
	std::map<std::string, AlgoExecution<Bond>> algoexecutionMap; // we have a algo execution for each corresponding product
	std::vector<ServiceListener<AlgoExecution<Bond>>*> listeners;

};

BondAlgoExecutionService::BondAlgoExecutionService() : algoexecutionMap(std::map<std::string, AlgoExecution<Bond>>()), listeners(std::vector<ServiceListener<AlgoExecution<Bond>>*>())
{

}

// Get data on our service given a key
AlgoExecution<Bond>& BondAlgoExecutionService::GetData(std::string key)
{
	return algoexecutionMap.at(key);
}

// The callback that a Connector should invoke for any new or updated data
void BondAlgoExecutionService::OnMessage(AlgoExecution<Bond>& data)
{

}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
void BondAlgoExecutionService::AddListener(ServiceListener<AlgoExecution<Bond>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
const std::vector< ServiceListener<AlgoExecution<Bond>>*>& BondAlgoExecutionService::GetListeners() const
{
	return listeners;
}


// check if algo wants to send order
bool BondAlgoExecutionService::GoodToSend(const OrderBook<Bond>& orderBook)
{
	// in this case, we check whether the spread is small enough (<=1/128)
	std::vector<Order> bidOrders = orderBook.GetBidStack();
	std::vector<Order> offerOrders = orderBook.GetOfferStack();
	Order bestBid = *(std::max_element(bidOrders.begin(), bidOrders.end()));
	Order bestOffer = *(std::max_element(offerOrders.begin(), offerOrders.end()));
	double bestBidPrice = bestBid.GetPrice();
	double bestOfferPrice = bestOffer.GetPrice();
	double spread = bestOfferPrice - bestBidPrice;
	bool goodToSend = spread <= 1.0 / 128.0 ? true : false;

	//if (goodToSend) std::cout << "Good to send, spread: " << spread << std::endl;
	//else std::cout << "Not good to send, spread: " << spread << std::endl;
		
	return goodToSend;
}

// update execution order when given an order book
void BondAlgoExecutionService::AddOrderBook(const OrderBook<Bond>& orderBook)
{
	Bond product = orderBook.GetProduct();
	std::string id = product.GetProductId();

	auto it = algoexecutionMap.find(id);
	if (it == algoexecutionMap.end())
	{// algo execution not already in map
		algoexecutionMap.insert(std::pair<std::string, AlgoExecution<Bond>>(id, AlgoExecution<Bond>(orderBook)));
	}
	it = algoexecutionMap.find(id);
	it->second.UpdateExecutionOrder(orderBook);

	// if spread is small enough, good to send order and let listeners know
	if (GoodToSend(orderBook))
	{
		for (auto& listener : listeners)
		{
			listener->ProcessAdd(it->second);
		}
	}

}


#endif