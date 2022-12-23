#ifndef BOND_TRADE_BOOKING_SERVICE_LISTENER_HPP
#define BOND_TRADE_BOOKING_SERVICE_LISTENER_HPP

#include "soa.hpp"
#include "products.hpp"
#include "bondTradeBookingService.hpp"
#include "executionservice.hpp"

class BondTradeBookingServiceListener : public ServiceListener<ExecutionOrder<Bond>>
{
public:
    BondTradeBookingServiceListener(BondTradeBookingService* _service);

    // Listener callback to process an add event to the Service
    virtual void ProcessAdd(ExecutionOrder<Bond>& data);

    // Listener callback to process a remove event to the Service
    virtual void ProcessRemove(ExecutionOrder<Bond>& data);

    // Listener callback to process an update event to the Service
    virtual void ProcessUpdate(ExecutionOrder<Bond>& data);

private:
    BondTradeBookingService* service;
};


BondTradeBookingServiceListener::BondTradeBookingServiceListener(BondTradeBookingService* _service) :
    service(_service)
{

}

// Listener callback to process an add event to the Service
void BondTradeBookingServiceListener::ProcessAdd(ExecutionOrder<Bond>& data)
{
    // create Trade from the execution order
    Bond product = data.GetProduct();
    std::string tradeId = "TRADE" + data.GetOrderId();
    OrderType orderType = data.GetOrderType();
    double price = data.GetPrice();
    std::string book = "EXECUTIONBOOK";
    long visibleQuantity = data.GetVisibleQuantity();
    long hiddenQuantity = data.GetHiddenQuantity();
    Side side = (data.GetPricingSide() == BID ? SELL : BUY);
    Trade<Bond> trade(product, tradeId, price, book, visibleQuantity, side);

    // tell TradeBookingService to book trade
    service->BookTrade(trade);
}

// Listener callback to process a remove event to the Service
void BondTradeBookingServiceListener::ProcessRemove(ExecutionOrder<Bond>& data)
{

}

// Listener callback to process an update event to the Service
void BondTradeBookingServiceListener::ProcessUpdate(ExecutionOrder<Bond>& data)
{

}







#endif