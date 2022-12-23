#ifndef BOND_TRADE_BOOKING_SERVICE_HPP
#define BOND_TRADE_BOOKING_SERVICE_HPP

#include "tradebookingservice.hpp"
#include "products.hpp"
#include <string>


class BondTradeBookingService : public TradeBookingService<Bond>
{
public:
	BondTradeBookingService();

	// Get data on our service given a key
	virtual Trade<Bond>& GetData(std::string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Trade<Bond>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Trade<Bond>>* listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Trade<Bond>>*>& GetListeners() const;

	// Book the trade
	void BookTrade(Trade<Bond>& trade);


private:
	std::map<std::string, Trade<Bond>> tradeMap;
	std::vector<ServiceListener<Trade<Bond>>*> listeners;
};

BondTradeBookingService::BondTradeBookingService() : tradeMap(std::map<std::string, Trade<Bond>>()), listeners(std::vector<ServiceListener<Trade<Bond>>*>())
{

}

Trade<Bond>& BondTradeBookingService::GetData(std::string key)
{
	return tradeMap.at(key);
}

void BondTradeBookingService::OnMessage(Trade<Bond>& data)
{
	BookTrade(data);
}

void BondTradeBookingService::AddListener(ServiceListener<Trade<Bond>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
const vector<ServiceListener<Trade<Bond>>*>& BondTradeBookingService::GetListeners() const
{
	return listeners;
}

void BondTradeBookingService::BookTrade(Trade<Bond>& trade)
{
	std::string id = trade.GetTradeId();
	auto it = tradeMap.find(id);
	if (it != tradeMap.end()) // if in the map already
	{
		tradeMap.erase(id);
	}
	tradeMap.insert(std::pair<std::string, Trade<Bond>>(id, trade));

	// call ProcessAdd on all listeners
	for (auto& listener : listeners)
	{
		listener->ProcessAdd(trade); // to bondPositionServiceListener
	}
}

#endif