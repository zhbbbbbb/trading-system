#ifndef BOND_STREAMING_SERVICE_LISTENER_HPP
#define BOND_STREAMING_SERVICE_LISTENER_HPP


#include "soa.hpp"
#include "products.hpp"
#include "streamingservice.hpp"
#include "bondAlgoStreamingService.hpp"
#include "bondStreamingService.hpp"

class BondStreamingServiceListener : public ServiceListener<AlgoStream<Bond>>
{
public:
    BondStreamingServiceListener(BondStreamingService* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(AlgoStream<Bond>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(AlgoStream<Bond>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(AlgoStream<Bond>& data);

private:
    BondStreamingService* service;
};


BondStreamingServiceListener::BondStreamingServiceListener(BondStreamingService* _service) :
    service(_service)
{

}

// Listener callback to process an add event to the Service
void BondStreamingServiceListener::ProcessAdd(AlgoStream<Bond>& data)
{
    service->AddAlgoStream(data);
}

// Listener callback to process a remove event to the Service
void BondStreamingServiceListener::ProcessRemove(AlgoStream<Bond>& data)
{

}

// Listener callback to process an update event to the Service
void BondStreamingServiceListener::ProcessUpdate(AlgoStream<Bond>& data)
{

}













#endif