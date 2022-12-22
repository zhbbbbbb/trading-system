#ifndef BOND_GUI_SERVICE_LISTENER_HPP
#define BOND_GUI_SERVICE_LISTENER_HPP

#include "bondGUIService.hpp"
#include "pricingservice.hpp"
#include "products.hpp"
#include "soa.hpp"
#include <vector>
#include <map>
#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"


class BondGUIServiceListener : public ServiceListener<Price<Bond>>
{// listens to BondAlgoPricingService
public:
    BondGUIServiceListener(BondGUIService* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(Price<Bond>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(Price<Bond>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(Price<Bond>& data);

private:
    BondGUIService* service;
};


BondGUIServiceListener::BondGUIServiceListener(BondGUIService* _service) :
    service(_service)
{

}

// Listener callback to process an add event to the Service
void BondGUIServiceListener::ProcessAdd(Price<Bond>& data)
{
    service->OnMessage(data);
}

// Listener callback to process a remove event to the Service
void BondGUIServiceListener::ProcessRemove(Price<Bond>& data)
{

}

// Listener callback to process an update event to the Service
void BondGUIServiceListener::ProcessUpdate(Price<Bond>& data)
{

}















#endif