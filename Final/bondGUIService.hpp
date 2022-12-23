#ifndef BOND_GUI_SERVICE_HPP
#define BOND_GUI_SERVICE_HPP

#include "guiservice.hpp"
#include "bondGUIServiceConnector.hpp"
#include "pricingservice.hpp"
#include "products.hpp"
#include "soa.hpp"
#include <vector>
#include <map>
#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"
using boost::posix_time::ptime;
using boost::posix_time::microsec_clock;
using boost::posix_time::time_duration;
using boost::posix_time::microsec_clock;
using boost::posix_time::millisec;

//This should be keyed on product identifier with value a Price object(from PricingService).
//The GUIService is a GUI component that listens to streaming prices that should be throettled.
//Define the GUIService with a 300 millisecond throttle.You only need to print the first 100 updates.
//It should register a ServiceListener on the BondPricingService with the specified throttle,
//which should notify back to the GUIService at that throttle interval.
//The GUIService should output those updates with a timestamp with millisecond precision to a file gui.txt.


class BondGUIService : public GUIService<Bond>
{
public:
	BondGUIService();

	// Get data on our service given a key
	virtual Price<Bond>& GetData(std::string key);

	virtual BondGUIServiceConnector& GetConnector() const;

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Price<Bond>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Price<Bond>>* listener);

	// Get all listeners on the Service.
	virtual const std::vector<ServiceListener<Price<Bond>>*>& GetListeners() const;

private:
	static time_duration throttle;
	BondGUIServiceConnector* connector;
	ptime prevTime;
	std::map<std::string, Price<Bond>> priceMap;
	std::vector<ServiceListener<Price<Bond>>*> listeners;
};


time_duration BondGUIService::throttle = millisec(300);


BondGUIService::BondGUIService() :
	connector(new BondGUIServiceConnector()), prevTime(microsec_clock::local_time()), priceMap(std::map<std::string, Price<Bond>>()), listeners(std::vector<ServiceListener<Price<Bond>>*>())
{

}

// Get data on our service given a key
Price<Bond>& BondGUIService::GetData(std::string key)
{
	return priceMap.at(key);
}

BondGUIServiceConnector& BondGUIService::GetConnector() const
{
	return *connector;
}

// The callback that a Connector should invoke for any new or updated data
void BondGUIService::OnMessage(Price<Bond>& data)
{// update on new Price from listener
	// at each throttle
	ptime nowTime = microsec_clock::local_time();
	time_duration duration = nowTime - prevTime;
	if (duration >= throttle)
	{// only when more than 300 milliseconds have passed
		prevTime = nowTime;
		Bond product = data.GetProduct();
		std::string id = product.GetProductId();
		auto it = priceMap.find(id);
		if (it != priceMap.end())
		{// if in map, first erase
			priceMap.erase(id);
		}
		priceMap.insert(std::pair<std::string, Price<Bond>>(id, data));

		connector->Publish(data, nowTime);
		for (auto& listener : listeners)
		{
			listener->ProcessAdd(data);
		}
	}
}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
void BondGUIService::AddListener(ServiceListener<Price<Bond>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
const std::vector<ServiceListener<Price<Bond>>*>& BondGUIService::GetListeners() const
{
	return listeners;
}

#endif