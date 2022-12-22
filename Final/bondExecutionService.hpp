#ifndef BOND_EXECUTION_SERVICE_HPP
#define BOND_EXECUTION_SERVICE_HPP

#include "executionservice.hpp"
#include "bondExecutionServiceConnector.hpp"
#include "soa.hpp"
#include "products.hpp"
#include <vector>
#include <map>
#include <string>



class BondExecutionService : public ExecutionService<Bond>
{
public:

public:
	BondExecutionService();

	// Get data on our service given a key
	virtual ExecutionOrder<Bond>& GetData(std::string key);

	// Get connector
	virtual BondExecutionServiceConnector& GetConnector() const;

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(ExecutionOrder<Bond>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<ExecutionOrder<Bond>>* listener);

	// Get all listeners on the Service.
	virtual const vector<ServiceListener<ExecutionOrder<Bond>>*>& GetListeners() const;

	// Execute an order on a market
	virtual void ExecuteOrder(ExecutionOrder<Bond>& order, Market market);

	// when a new algo execution is received, update executionorderMap
	virtual void AddAlgoExecution(const AlgoExecution<Bond>& algoExecution);

private:
	std::map<std::string, ExecutionOrder<Bond>> executionorderMap;
	std::vector<ServiceListener<ExecutionOrder<Bond>>*> listeners;
	BondExecutionServiceConnector* connector;

};

BondExecutionService::BondExecutionService() : executionorderMap(std::map<std::string, ExecutionOrder<Bond>>()), listeners(std::vector<ServiceListener<ExecutionOrder<Bond>>*>()), connector(new BondExecutionServiceConnector())
{

}

// Get data on our service given a key
ExecutionOrder<Bond>& BondExecutionService::GetData(std::string key)
{
	return executionorderMap.at(key);
}

// Get data on our service given a key
BondExecutionServiceConnector& BondExecutionService::GetConnector() const
{
	return *connector;
}


// The callback that a Connector should invoke for any new or updated data
void BondExecutionService::OnMessage(ExecutionOrder<Bond>& data)
{

}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
void BondExecutionService::AddListener(ServiceListener<ExecutionOrder<Bond>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
const vector<ServiceListener<ExecutionOrder<Bond>>*>& BondExecutionService::GetListeners() const
{
	return listeners;
}

void BondExecutionService::ExecuteOrder(ExecutionOrder<Bond>& order, Market market)
{
	// nothing to do with market in current version. Implementable when there's an Exchange class
	// save execution order and tell BondTradeBookingListener
	std::string id = order.GetProduct().GetProductId();
	auto it = executionorderMap.find(id);
	if (it != executionorderMap.end())
	{
		executionorderMap.erase(id);
	}
	executionorderMap.insert(std::pair<std::string, ExecutionOrder<Bond>>(id, order));
	connector->Publish(order);// tell connector to publish this order
	for (auto& listener : listeners)
	{
		listener->ProcessAdd(order);
	}

}


// when a new algo execution is received, update executionorderMap
void BondExecutionService::AddAlgoExecution(const AlgoExecution<Bond>& algoExecution)
{
	ExecutionOrder<Bond> executionOrder = algoExecution.GetExecutionOrder();
	ExecutionOrder<Bond> order = algoExecution.GetExecutionOrder();

	//market: BROKERTEC, ESPEED, CME
	ExecuteOrder(order, BROKERTEC);// execute all orders on BROKERTEC for now. No implementation for market selection yet
}








#endif