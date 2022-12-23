#ifndef GENERIC_HISTORICAL_DATA_SERVICE_LISTENER_HPP
#define GENERIC_HISTORICAL_DATA_SERVICE_LISTENER_HPP

#include "genericHistoricalDataService.hpp"
#include "historicaldataservice.hpp"
#include "positionservice.hpp"
#include "riskservice.hpp"
#include "executionservice.hpp"
#include "streamingservice.hpp"
#include "inquiryservice.hpp"
#include "soa.hpp"
#include "products.hpp"

#include <vector>
#include <map>
#include <string>


template <typename T>
class PositionHistoricalDataServiceListener : public ServiceListener<Position<T>>
{
public:
    PositionHistoricalDataServiceListener(PositionHistoricalDataService<T>* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(Position<T>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(Position<T>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(Position<T>& data);
private:
    PositionHistoricalDataService<T>* service;
};

template <typename T>
class RiskHistoricalDataServiceListener : public ServiceListener<PV01<T>>
{
public:
    RiskHistoricalDataServiceListener(RiskHistoricalDataService<T>* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(PV01<T>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(PV01<T>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(PV01<T>& data);
private:
    RiskHistoricalDataService<T>* service;
};

template <typename T>
class ExecutionHistoricalDataServiceListener : public ServiceListener<ExecutionOrder<T>>
{
public:
    ExecutionHistoricalDataServiceListener(ExecutionHistoricalDataService<T>* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(ExecutionOrder<T>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(ExecutionOrder<T>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(ExecutionOrder<T>& data);
private:
    ExecutionHistoricalDataService<T>* service;
};

template <typename T>
class StreamingHistoricalDataServiceListener : public ServiceListener<PriceStream<T>>
{
public:
    StreamingHistoricalDataServiceListener(StreamingHistoricalDataService<T>* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(PriceStream<T>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(PriceStream<T>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(PriceStream<T>& data);
private:
    StreamingHistoricalDataService<T>* service;
};

template <typename T>
class InquiryHistoricalDataServiceListener : public ServiceListener<Inquiry<T>>
{
public:
    InquiryHistoricalDataServiceListener(InquiryHistoricalDataService<T>* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(Inquiry<T>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(Inquiry<T>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(Inquiry<T>& data);
private:
    InquiryHistoricalDataService<T>* service;
};

//////////////////////////////////////////////////////////////////////////////////////
template <typename T>
PositionHistoricalDataServiceListener<T>::PositionHistoricalDataServiceListener(PositionHistoricalDataService<T>* _service): service(_service)
{

}

template <typename T>
void PositionHistoricalDataServiceListener<T>::ProcessAdd(Position<T>& data)
{
    service->PersistData("", data);
}

template <typename T>
void PositionHistoricalDataServiceListener<T>::ProcessRemove(Position<T>& data) {}

template <typename T>
void PositionHistoricalDataServiceListener<T>::ProcessUpdate(Position<T>& data) {}
////////////////////////////////////////////////////////////////////////////////////
template <typename T>
RiskHistoricalDataServiceListener<T>::RiskHistoricalDataServiceListener(RiskHistoricalDataService<T>* _service) : service(_service)
{

}


template <typename T>
void RiskHistoricalDataServiceListener<T>::ProcessAdd(PV01<T>& data)
{
    service->PersistData("", data);
}

template <typename T>
void RiskHistoricalDataServiceListener<T>::ProcessRemove(PV01<T>& data) {}

template <typename T>
void RiskHistoricalDataServiceListener<T>::ProcessUpdate(PV01<T>& data) {}
////////////////////////////////////////////////////////////////////////////////////
template <typename T>
ExecutionHistoricalDataServiceListener<T>::ExecutionHistoricalDataServiceListener(ExecutionHistoricalDataService<T>* _service) : service(_service)
{

}


template <typename T>
void ExecutionHistoricalDataServiceListener<T>::ProcessAdd(ExecutionOrder<T>& data)
{
    service->PersistData("", data);
}

template <typename T>
void ExecutionHistoricalDataServiceListener<T>::ProcessRemove(ExecutionOrder<T>& data) {}

template <typename T>
void ExecutionHistoricalDataServiceListener<T>::ProcessUpdate(ExecutionOrder<T>& data) {}
////////////////////////////////////////////////////////////////////////////////////
template <typename T>
StreamingHistoricalDataServiceListener<T>::StreamingHistoricalDataServiceListener(StreamingHistoricalDataService<T>* _service) : service(_service)
{

}


template <typename T>
void StreamingHistoricalDataServiceListener<T>::ProcessAdd(PriceStream<T>& data)
{
    service->PersistData("", data);
}

template <typename T>
void StreamingHistoricalDataServiceListener<T>::ProcessRemove(PriceStream<T>& data) {}

template <typename T>
void StreamingHistoricalDataServiceListener<T>::ProcessUpdate(PriceStream<T>& data) {}
////////////////////////////////////////////////////////////////////////////////////
template <typename T>
InquiryHistoricalDataServiceListener<T>::InquiryHistoricalDataServiceListener(InquiryHistoricalDataService<T>* _service) : service(_service)
{

}


template <typename T>
void InquiryHistoricalDataServiceListener<T>::ProcessAdd(Inquiry<T>& data)
{
    service->PersistData("", data);
}

template <typename T>
void InquiryHistoricalDataServiceListener<T>::ProcessRemove(Inquiry<T>& data) {}

template <typename T>
void InquiryHistoricalDataServiceListener<T>::ProcessUpdate(Inquiry<T>& data) {}
////////////////////////////////////////////////////////////////////////////////////









#endif