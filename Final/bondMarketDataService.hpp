#ifndef BOND_MARKET_DATA_SERVICE_HPP
#define BOND_MARKET_DATA_SERVICE_HPP

#include "marketdataservice.hpp"
#include "products.hpp"
#include <vector>
#include <map>
#include <string>

class BondMarketDataService : public MarketDataService<Bond>
{
public:
	BondMarketDataService();

	// Get data on our service given a key
	virtual OrderBook<Bond>& GetData(std::string key);

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(OrderBook<Bond>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<OrderBook<Bond>>* listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<OrderBook<Bond>>*>& GetListeners() const;

	// Get the best bid/offer order
    virtual BidOffer GetBestBidOffer(const string& productId);

    // Aggregate the order book
    virtual OrderBook<Bond> AggregateDepth(const string& productId);

private:
	std::map<std::string, OrderBook<Bond>> marketdataMap;
	std::vector<ServiceListener<OrderBook<Bond>>*> listeners;


};


BondMarketDataService::BondMarketDataService() : marketdataMap(std::map<std::string, OrderBook<Bond>>()), listeners(std::vector<ServiceListener<OrderBook<Bond>>*>())
{

}

// Get data on our service given a key
OrderBook<Bond>& BondMarketDataService::GetData(std::string key)
{
	return marketdataMap.at(key);
}

// The callback that a Connector should invoke for any new or updated data
void BondMarketDataService::OnMessage(OrderBook<Bond>& data)
{
	std::string id = data.GetProduct().GetProductId();
	auto it = marketdataMap.find(id);
	if (it != marketdataMap.end()) 
	{// if in the map already, then erase before updating
		marketdataMap.erase(id);
	}
	marketdataMap.insert(std::pair<std::string, OrderBook<Bond>>(id, data));

	// aggregate orderbook
	OrderBook<Bond> aggOrderBook = AggregateDepth(id);

	// call ProcessAdd on all listeners
	for (auto& listener : listeners)
	{
		listener->ProcessAdd(aggOrderBook);
	}
}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
void BondMarketDataService::AddListener(ServiceListener<OrderBook<Bond>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
const vector< ServiceListener<OrderBook<Bond>>*>& BondMarketDataService::GetListeners() const
{
	return listeners;
}

// Get the best bid/offer order
BidOffer BondMarketDataService::GetBestBidOffer(const string& productId)
{
	OrderBook<Bond> ob = marketdataMap.at(productId);
	std::vector<Order> bids = ob.GetBidStack();
	Order bestBid = bids[0];
	std::vector<Order> offers = ob.GetOfferStack();
	Order bestOffer = offers[0];

	for (auto& bid : bids)
	{
		if (bid.GetPrice() > bestBid.GetPrice())
		{
			bestBid = bid;
		}
	}
	for (auto& offer : offers)
	{
		if (offer.GetPrice() < bestOffer.GetPrice())
		{
			bestOffer = offer;
		}
	}
	return BidOffer(bestBid, bestOffer);
}

// Aggregate the order book
OrderBook<Bond> BondMarketDataService::AggregateDepth(const string& productId)
{
	OrderBook<Bond> ob = marketdataMap.at(productId);
	std::vector<Order> bids = ob.GetBidStack();
	std::vector<Order> offers = ob.GetOfferStack();
	std::map<double, long> bids2, offers2; // aggregate in a price-quantity map
	std::vector<Order> bids3, offers3;	// transform bids2/offers2 (map) into bids3/offers3 (vector) later
	double price;
	long quantity;
	for (auto& bid : bids)
	{
		price = bid.GetPrice();
		quantity = bid.GetQuantity();
		if (bids2.find(price) != bids2.end())
		{// if not in bids2
			bids2.insert(std::pair<double, long>(price, quantity));
		}
		else
		{// if already in bids2
			bids2[price] += quantity;
		}
	}
	for (auto& offer : offers)
	{
		price = offer.GetPrice();
		quantity = offer.GetQuantity();
		if (offers2.find(price) != offers2.end())
		{// if not in offers2
			offers2.insert(std::pair<double, long>(price, quantity));
		}
		else
		{// if already in offers2
			offers2[price] += quantity;
		}
	}
	for (auto& bid : bids2) bids3.push_back(Order(bid.first, bid.second, BID));
	for (auto& offer : offers2) offers3.push_back(Order(offer.first, offer.second, OFFER));
	return OrderBook<Bond>(ob.GetProduct(), bids3, offers3);
}


#endif