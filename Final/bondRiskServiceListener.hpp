#ifndef BOND_RISK_SERVICE_LISTENER_HPP
#define BOND_RISK_SERVICE_LISTENER_HPP

#include "riskservice.hpp"
#include "bondRiskService.hpp"
#include "soa.hpp"
#include "products.hpp"
#include "bondpositionservice.hpp"
#include <map>
#include <vector>
#include <string>


// this listener listens for Position from BondPositionService
class BondRiskServiceListener : public ServiceListener<Position<Bond>>
{
public:
    BondRiskServiceListener(BondRiskService* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(Position<Bond>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(Position<Bond>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(Position<Bond>& data);

private:
    BondRiskService* service;
};


BondRiskServiceListener::BondRiskServiceListener(BondRiskService* _service) :
    service(_service)
{

}

// Listener callback to process an add event to the Service
void BondRiskServiceListener::ProcessAdd(Position<Bond>& data)
{
    service->AddPosition(data);
    // this will tell the bond trade booking service listener

}

// Listener callback to process a remove event to the Service
void BondRiskServiceListener::ProcessRemove(Position<Bond>& data)
{

}

// Listener callback to process an update event to the Service
void BondRiskServiceListener::ProcessUpdate(Position<Bond>& data)
{

}





#endif