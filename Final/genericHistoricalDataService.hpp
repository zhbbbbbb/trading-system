#ifndef GENERIC_HISTORICAL_DATA_SERVICE_HPP
#define GENERIC_HISTORICAL_DATA_SERVICE_HPP

#include "historicaldataservice.hpp"
#include "genericHistoricalDataServiceConnector.hpp"
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
class PositionHistoricalDataService : public HistoricalDataService<Position<T>>
{
public:
	PositionHistoricalDataService();

	// Get data on our service given a key
	virtual Position<T>& GetData(std::string key);

	// get connector
	virtual PositionHistoricalDataServiceConnector<T>& GetConnector() const;

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Position<T>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Position<T>>* listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Position<T>>*>& GetListeners() const;

	// Persist data to a store
	void PersistData(std::string persistKey, Position<T>& data);

private:
	std::map<std::string, Position<T>> dataMap;
	std::vector<ServiceListener<Position<T>>*> listeners;
	PositionHistoricalDataServiceConnector<T>* connector;
};

template <typename T>
class RiskHistoricalDataService : public HistoricalDataService<PV01<T>>
{
public:
	RiskHistoricalDataService();

	// Get data on our service given a key
	virtual PV01<T>& GetData(std::string key);

	// get connector
	virtual RiskHistoricalDataServiceConnector<T>& GetConnector() const;

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PV01<T>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<PV01<T>>* listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<PV01<T>>*>& GetListeners() const;

	// Get the bucketed risk for the bucket sector, same implementation as BondRiskService
	virtual const PV01<BucketedSector<Bond>> GetBucketedRisk(const BucketedSector<Bond>& sector) const;

	// also record bucketed sectors' risks
	virtual void AddBucketedSector(const BucketedSector<T>& sector);

	// Persist data to a store
	virtual void PersistData(std::string persistKey, PV01<T>& data);

private:
	std::map<std::string, PV01<T>> dataMap;
	std::vector<ServiceListener<PV01<T>>*> listeners;
	RiskHistoricalDataServiceConnector<T>* connector;
	std::vector<BucketedSector<T>> sectors;// also record bucketed sectors' risks
};


template <typename T>
class ExecutionHistoricalDataService : public HistoricalDataService<ExecutionOrder<T>>
{
public:
	ExecutionHistoricalDataService();

	// Get data on our service given a key
	virtual ExecutionOrder<T>& GetData(std::string key);

	// get connector
	virtual ExecutionHistoricalDataServiceConnector<T>& GetConnector() const;

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(ExecutionOrder<T>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<ExecutionOrder<T>>* listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<ExecutionOrder<T>>*>& GetListeners() const;

	// Persist data to a store
	virtual void PersistData(std::string persistKey, ExecutionOrder<T>& data);

private:
	std::map<std::string, ExecutionOrder<T>> dataMap;
	std::vector<ServiceListener<ExecutionOrder<T>>*> listeners;
	ExecutionHistoricalDataServiceConnector<T>* connector;
};


template <typename T>
class StreamingHistoricalDataService : public HistoricalDataService<PriceStream<T>>
{
public:
	StreamingHistoricalDataService();

	// Get data on our service given a key
	virtual PriceStream<T>& GetData(std::string key);

	// get connector
	virtual StreamingHistoricalDataServiceConnector<T>& GetConnector() const;

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(PriceStream<T>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<PriceStream<T>>* listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<PriceStream<T>>*>& GetListeners() const;

	// Persist data to a store
	void PersistData(std::string persistKey, PriceStream<T>& data);

private:
	std::map<std::string, PriceStream<T>> dataMap;
	std::vector<ServiceListener<PriceStream<T>>*> listeners;
	StreamingHistoricalDataServiceConnector<T>* connector;
};


template <typename T>
class InquiryHistoricalDataService : public HistoricalDataService<Inquiry<T>>
{
public:
	InquiryHistoricalDataService();

	// Get data on our service given a key
	virtual Inquiry<T>& GetData(std::string key);

	// get connector
	virtual InquiryHistoricalDataServiceConnector<T>& GetConnector() const;


	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Inquiry<T>& data);

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Inquiry<T>>* listener);

	// Get all listeners on the Service.
	virtual const vector< ServiceListener<Inquiry<T>>*>& GetListeners() const;

	// Persist data to a store
	void PersistData(std::string persistKey, Inquiry<T>& data);

private:
	std::map<std::string, Inquiry<T>> dataMap; // note that this is keyed on inquiry id not product id
	std::vector<ServiceListener<Inquiry<T>>*> listeners;
	InquiryHistoricalDataServiceConnector<T>* connector;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
PositionHistoricalDataService<T>::PositionHistoricalDataService() :
	dataMap(std::map<std::string, Position<T>>()), listeners(std::vector<ServiceListener<Position<T>>*>()), connector(new PositionHistoricalDataServiceConnector<T>())
{

}

// Get data on our service given a key
template <typename T>
Position<T>& PositionHistoricalDataService<T>::GetData(std::string key)
{
	return dataMap.at(key);
}

// get connector
template <typename T>
PositionHistoricalDataServiceConnector<T>& PositionHistoricalDataService<T>::GetConnector() const
{
	return *connector;
}

// The callback that a Connector should invoke for any new or updated data
template <typename T>
void PositionHistoricalDataService<T>::OnMessage(Position<T>& data)
{
	PersistData("", data);
}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
template <typename T>
void PositionHistoricalDataService<T>::AddListener(ServiceListener<Position<T>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
template <typename T>
const vector< ServiceListener<Position<T>>*>& PositionHistoricalDataService<T>::GetListeners() const
{
	return listeners;
}

// Persist data to a store
template <typename T>
void PositionHistoricalDataService<T>::PersistData(std::string persistKey, Position<T>& data)
{
	std::string id = data.GetProduct().GetProductId();
	auto it = dataMap.find(id);
	if (it != dataMap.end())
	{
		dataMap.erase(id);
	}
	dataMap.insert(std::pair<std::string, Position<T>>(id, data));
	connector->Publish(data);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
RiskHistoricalDataService<T>::RiskHistoricalDataService() :
	dataMap(std::map<std::string, PV01<T>>()), listeners(std::vector<ServiceListener<PV01<T>>*>()), connector(new RiskHistoricalDataServiceConnector<T>()), sectors(std::vector<BucketedSector<T>>())
{

}

// Get data on our service given a key
template <typename T>
PV01<T>& RiskHistoricalDataService<T>::GetData(std::string key)
{
	return dataMap.at(key);
}

// get connector
template <typename T>
RiskHistoricalDataServiceConnector<T>& RiskHistoricalDataService<T>::GetConnector() const
{
	return *connector;
}

// The callback that a Connector should invoke for any new or updated data
template <typename T>
void RiskHistoricalDataService<T>::OnMessage(PV01<T>& data)
{
	PersistData("", data);
}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
template <typename T>
void RiskHistoricalDataService<T>::AddListener(ServiceListener<PV01<T>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
template <typename T>
const vector< ServiceListener<PV01<T>>*>& RiskHistoricalDataService<T>::GetListeners() const
{
	return listeners;
}

// Get the bucketed risk for the bucket sector
template <typename T>
const PV01<BucketedSector<Bond>> RiskHistoricalDataService<T>::GetBucketedRisk(const BucketedSector<Bond>& sector) const
{
	double pv01;
	long quantity;
	double pv01Total = 0;
	long quantityTotal = 0;
	std::string id;
	for (const auto& product : sector.GetProducts())
	{
		id = product.GetProductId();
		auto it = dataMap.find(id);
		if (it != dataMap.end())
		{// if the product is in the riskMap
			pv01 = it->second.GetPV01();
			quantity = it->second.GetQuantity();
			pv01Total += pv01 * ((double)quantity);
			quantityTotal += quantity;
		}
	}
	if (quantityTotal != 0)
	{
		pv01Total /= ((double)quantityTotal); // PV01Total is the quantity-weighted average PV01
	}
	return PV01<BucketedSector<Bond>>(sector, pv01Total, quantityTotal);
}

// also record bucketed sectors' risks
template <typename T>
void RiskHistoricalDataService<T>::AddBucketedSector(const BucketedSector<T>& sector)
{
	sectors.push_back(sector);
}

// Persist data to a store
template <typename T>
void RiskHistoricalDataService<T>::PersistData(std::string persistKey, PV01<T>& data)
{
	std::string id = data.GetProduct().GetProductId();
	auto it = dataMap.find(id);
	if (it != dataMap.end())
	{
		dataMap.erase(id);
	}
	dataMap.insert(std::pair<std::string, PV01<T>>(id, data));

	// if there are sectors of interest publish them as well
	if (sectors.size() > 0)
	{
		std::vector<PV01<BucketedSector<T>>> pv01s;
		for (const auto& sector : sectors)
		{
			pv01s.push_back(this->GetBucketedRisk(sector));
		}
		connector->Publish(data, pv01s);
	}
	else
	{
		connector->Publish(data);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
ExecutionHistoricalDataService<T>::ExecutionHistoricalDataService() :
	dataMap(std::map<std::string, ExecutionOrder<T>>()), listeners(std::vector<ServiceListener<ExecutionOrder<T>>*>()), connector(new ExecutionHistoricalDataServiceConnector<T>())
{

}

// Get data on our service given a key
template <typename T>
ExecutionOrder<T>& ExecutionHistoricalDataService<T>::GetData(std::string key)
{
	return dataMap.at(key);
}

// get connector
template <typename T>
ExecutionHistoricalDataServiceConnector<T>& ExecutionHistoricalDataService<T>::GetConnector() const
{
	return *connector;
}

// The callback that a Connector should invoke for any new or updated data
template <typename T>
void ExecutionHistoricalDataService<T>::OnMessage(ExecutionOrder<T>& data)
{
	PersistData("", data);
}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
template <typename T>
void ExecutionHistoricalDataService<T>::AddListener(ServiceListener<ExecutionOrder<T>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
template <typename T>
const vector< ServiceListener<ExecutionOrder<T>>*>& ExecutionHistoricalDataService<T>::GetListeners() const
{
	return listeners;
}

// Persist data to a store
template <typename T>
void ExecutionHistoricalDataService<T>::PersistData(std::string persistKey, ExecutionOrder<T>& data)
{
	std::string id = data.GetProduct().GetProductId();
	auto it = dataMap.find(id);
	if (it != dataMap.end())
	{
		dataMap.erase(id);
	}
	dataMap.insert(std::pair<std::string, ExecutionOrder<T>>(id, data));
	connector->Publish(data);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
StreamingHistoricalDataService<T>::StreamingHistoricalDataService() :
	dataMap(std::map<std::string, PriceStream<T>>()), listeners(std::vector<ServiceListener<PriceStream<T>>*>()), connector(new StreamingHistoricalDataServiceConnector<T>())
{

}

// Get data on our service given a key
template <typename T>
PriceStream<T>& StreamingHistoricalDataService<T>::GetData(std::string key)
{
	return dataMap.at(key);
}

// get connector
template <typename T>
StreamingHistoricalDataServiceConnector<T>& StreamingHistoricalDataService<T>::GetConnector() const
{
	return *connector;
}

// The callback that a Connector should invoke for any new or updated data
template <typename T>
void StreamingHistoricalDataService<T>::OnMessage(PriceStream<T>& data)
{
	PersistData("", data);
}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
template <typename T>
void StreamingHistoricalDataService<T>::AddListener(ServiceListener<PriceStream<T>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
template <typename T>
const vector< ServiceListener<PriceStream<T>>*>& StreamingHistoricalDataService<T>::GetListeners() const
{
	return listeners;
}

// Persist data to a store
template <typename T>
void StreamingHistoricalDataService<T>::PersistData(std::string persistKey, PriceStream<T>& data)
{
	std::string id = data.GetProduct().GetProductId();
	auto it = dataMap.find(id);
	if (it != dataMap.end())
	{
		dataMap.erase(id);
	}
	dataMap.insert(std::pair<std::string, PriceStream<T>>(id, data));
	connector->Publish(data);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
InquiryHistoricalDataService<T>::InquiryHistoricalDataService() :
	dataMap(std::map<std::string, Inquiry<T>>()), listeners(std::vector<ServiceListener<Inquiry<T>>*>()), connector(new InquiryHistoricalDataServiceConnector<T>())
{

}

// Get data on our service given a key
template <typename T>
Inquiry<T>& InquiryHistoricalDataService<T>::GetData(std::string key)
{
	return dataMap.at(key);
}

// get connector
template <typename T>
InquiryHistoricalDataServiceConnector<T>& InquiryHistoricalDataService<T>::GetConnector() const
{
	return *connector;
}

// The callback that a Connector should invoke for any new or updated data
template <typename T>
void InquiryHistoricalDataService<T>::OnMessage(Inquiry<T>& data)
{
	PersistData("", data);
}

// Add a listener to the Service for callbacks on add, remove, and update events
// for data to the Service.
template <typename T>
void InquiryHistoricalDataService<T>::AddListener(ServiceListener<Inquiry<T>>* listener)
{
	listeners.push_back(listener);
}

// Get all listeners on the Service.
template <typename T>
const vector< ServiceListener<Inquiry<T>>*>& InquiryHistoricalDataService<T>::GetListeners() const
{
	return listeners;
}

// Persist data to a store
template <typename T>
void InquiryHistoricalDataService<T>::PersistData(std::string persistKey, Inquiry<T>& data)
{
	std::string id = data.GetInquiryId(); // note that this is keyed on inquiry id not product id
	auto it = dataMap.find(id);
	if (it != dataMap.end())
	{
		dataMap.erase(id);
	}
	dataMap.insert(std::pair<std::string, Inquiry<T>>(id, data));
	connector->Publish(data);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
















#endif