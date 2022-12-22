#ifndef BOND_EXECUTION_SERVICE_LISTENER_HPP
#define BOND_EXECUTION_SERVICE_LISTENER_HPP


#include "executionservice.hpp"
#include "bondExecutionService.hpp"
#include "soa.hpp"
#include "products.hpp"


class BondExecutionServiceListener : public ServiceListener<AlgoExecution<Bond>>
{
public:
    BondExecutionServiceListener(BondExecutionService* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(AlgoExecution<Bond>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(AlgoExecution<Bond>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(AlgoExecution<Bond>& data);

private:
    BondExecutionService* service;
};


BondExecutionServiceListener::BondExecutionServiceListener(BondExecutionService* _service) :
    service(_service)
{

}

// Listener callback to process an add event to the Service
void BondExecutionServiceListener::ProcessAdd(AlgoExecution<Bond>& data)
{
    service->AddAlgoExecution(data);
}

// Listener callback to process a remove event to the Service
void BondExecutionServiceListener::ProcessRemove(AlgoExecution<Bond>& data)
{

}

// Listener callback to process an update event to the Service
void BondExecutionServiceListener::ProcessUpdate(AlgoExecution<Bond>& data)
{

}








#endif