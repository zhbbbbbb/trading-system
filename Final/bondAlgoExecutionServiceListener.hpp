#ifndef BOND_ALGO_EXECUTION_SERVICE_LISTENER_HPP
#define BOND_ALGO_EXECUTION_SERVICE_LISTENER_HPP

#include "executionservice.hpp"
#include "bondAlgoExecutionService.hpp"
#include "marketdataservice.hpp"
#include "soa.hpp"
#include "products.hpp"
#include <vector>
#include <map>
#include <string>


class BondAlgoExecutionServiceListener : public ServiceListener<OrderBook<Bond>>
{
public:
	BondAlgoExecutionServiceListener(BondAlgoExecutionService* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(OrderBook<Bond>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(OrderBook<Bond>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(OrderBook<Bond>& data);

private:
	BondAlgoExecutionService* service;
};


BondAlgoExecutionServiceListener::BondAlgoExecutionServiceListener(BondAlgoExecutionService* _service):
    service(_service)
{

}

// Listener callback to process an add event to the Service
void BondAlgoExecutionServiceListener::ProcessAdd(OrderBook<Bond>& data)
{
    service->AddOrderBook(data);
}

// Listener callback to process a remove event to the Service
void BondAlgoExecutionServiceListener::ProcessRemove(OrderBook<Bond>& data)
{

}

// Listener callback to process an update event to the Service
void BondAlgoExecutionServiceListener::ProcessUpdate(OrderBook<Bond>& data)
{

}









#endif