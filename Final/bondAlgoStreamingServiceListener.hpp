#ifndef BOND_ALGO_STREAMING_SERVICE_LISTENER_HPP
#define BOND_ALGO_STREAMING_SERVICE_LISTENER_HPP

#include "soa.hpp"
#include "streamingservice.hpp"
#include "pricingservice.hpp"
#include "products.hpp"
#include "bondAlgoStreamingService.hpp"

class BondAlgoStreamingServiceListener : public ServiceListener<Price<Bond>>
{
public:
    BondAlgoStreamingServiceListener(BondAlgoStreamingService* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(Price<Bond>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(Price<Bond>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(Price<Bond>& data);

private:
    BondAlgoStreamingService* service;
};


BondAlgoStreamingServiceListener::BondAlgoStreamingServiceListener(BondAlgoStreamingService* _service) :
    service(_service)
{

}

// Listener callback to process an add event to the Service
void BondAlgoStreamingServiceListener::ProcessAdd(Price<Bond>& data)
{
    service->AddPrice(data);
}

// Listener callback to process a remove event to the Service
void BondAlgoStreamingServiceListener::ProcessRemove(Price<Bond>& data)
{

}

// Listener callback to process an update event to the Service
void BondAlgoStreamingServiceListener::ProcessUpdate(Price<Bond>& data)
{

}




#endif