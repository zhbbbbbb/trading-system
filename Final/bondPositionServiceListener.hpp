#ifndef BOND_POSITION_SERVICE_LISTENER_HPP
#define BOND_POSITION_SERVICE_LISTENER_HPP

#include "positionservice.hpp"
#include "products.hpp"
#include "soa.hpp"
#include "bondPositionService.hpp"
#include "tradebookingservice.hpp"

class BondPositionServiceListener : public ServiceListener<Trade<Bond>>
{
public:
    BondPositionServiceListener(BondPositionService* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(Trade<Bond>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(Trade<Bond>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(Trade<Bond>& data);

private:
    BondPositionService* service;
};


BondPositionServiceListener::BondPositionServiceListener(BondPositionService* _service) :
    service(_service)
{

}

// Listener callback to process an add event to the Service
void BondPositionServiceListener::ProcessAdd(Trade<Bond>& data)
{
    service->AddTrade(data);
}

// Listener callback to process a remove event to the Service
void BondPositionServiceListener::ProcessRemove(Trade<Bond>& data)
{

}

// Listener callback to process an update event to the Service
void BondPositionServiceListener::ProcessUpdate(Trade<Bond>& data)
{

}










#endif