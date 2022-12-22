#ifndef GENERIC_HISTORICAL_DATA_SERVICE_CONNECTOR_HPP
#define GENERIC_HISTORICAL_DATA_SERVICE_CONNECTOR_HPP


#include "soa.hpp"
#include "products.hpp"
#include "positionservice.hpp"
#include "riskservice.hpp"
#include "executionservice.hpp"
#include "streamingservice.hpp"
#include "inquiryservice.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
using boost::posix_time::ptime;
using boost::posix_time::microsec_clock;

#include <vector>
#include <map>
#include <string>

// write to positions.txt, risk.txt, executions.txt, streaming.txt, allinquiries.txt 

template <typename T>
class PositionHistoricalDataServiceConnector : public Connector<Position<T>>
{
public:
	virtual void Publish(Position<T>& data);
	virtual void Subscribe(std::string filePath);
private:
	static std::string filePath; // output file path
};

template <typename T>
class RiskHistoricalDataServiceConnector : public Connector<PV01<T>>
{
public:
	virtual void Publish(PV01<T>& data); // just publish PV01 data
	virtual void Publish(PV01<T>& data, std::vector<PV01<BucketedSector<T>>> sectors); //publish PV01 as wells as interested bucketed sectors

	virtual void Subscribe(std::string filePath);
private:
	static std::string filePath; // output file path
	std::vector<BucketedSector<T>> sectors;
};


template <typename T>
class ExecutionHistoricalDataServiceConnector : public Connector<ExecutionOrder<T>>
{
public:
	virtual void Publish(ExecutionOrder<T>& data);

	virtual void Subscribe(std::string filePath);
private:
	static std::string filePath; // output file path
};

template <typename T>
class StreamingHistoricalDataServiceConnector : public Connector<PriceStream<T>>
{
public:
	virtual void Publish(PriceStream<T>& data);

	virtual void Subscribe(std::string filePath);
private:
	static std::string filePath; // output file path
};

template <typename T>
class InquiryHistoricalDataServiceConnector : public Connector<Inquiry<T>>
{
public:
	virtual void Publish(Inquiry<T>& data);

	virtual void Subscribe(std::string filePath);
private:
	static std::string filePath; // output file path
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// output file names

template <typename T>
std::string PositionHistoricalDataServiceConnector<T>::filePath = "positions.txt";
template <typename T>
std::string RiskHistoricalDataServiceConnector<T>::filePath = "risk.txt";
template <typename T>
std::string ExecutionHistoricalDataServiceConnector<T>::filePath = "executions.txt";
template <typename T>
std::string StreamingHistoricalDataServiceConnector<T>::filePath = "streaming.txt";
template <typename T>
std::string InquiryHistoricalDataServiceConnector<T>::filePath = "allinquiries.txt";


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// member functions definitions

template <typename T>
void PositionHistoricalDataServiceConnector<T>::Publish(Position<T>& data)
{
	// write to local txt file
	std::ofstream file;

	ptime now = microsec_clock::local_time();
	// append to original text
	file = std::ofstream(filePath, std::ofstream::out | std::ofstream::app);
	file << now << "," << data.str() << ",(Aggregate)" << data.GetAggregatePosition() << std::endl; // persist both each book and the aggregate
	file.close();
}

template <typename T>
void PositionHistoricalDataServiceConnector<T>::Subscribe(std::string filePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
void RiskHistoricalDataServiceConnector<T>::Publish(PV01<T>& data)
{
	// write to local txt file
	std::ofstream file;

	ptime now = microsec_clock::local_time();
	// append to original text
	file = std::ofstream(filePath, std::ofstream::out | std::ofstream::app);
	file << now << "," << data.str() << std::endl;
	file.close();
}


template <typename T>
void RiskHistoricalDataServiceConnector<T>::Publish(PV01<T>& data, std::vector<PV01<BucketedSector<T>>> sectorsPV01)
{
	// write to local txt file
	std::ofstream file;

	ptime now = microsec_clock::local_time();
	// append to original text
	file = std::ofstream(filePath, std::ofstream::out | std::ofstream::app);
	file << now << "," << data.str();

	for (const auto& pv01 : sectorsPV01)
	{// record the sector risks as well
		file << "{" << pv01.str() << "}";
	}
	file << std::endl;
	file.close();
}

template <typename T>
void RiskHistoricalDataServiceConnector<T>::Subscribe(std::string filePath)
{

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void ExecutionHistoricalDataServiceConnector<T>::Publish(ExecutionOrder<T>& data)
{
	// write to local txt file
	std::ofstream file;

	ptime now = microsec_clock::local_time();
	// append to original text
	file = std::ofstream(filePath, std::ofstream::out | std::ofstream::app);
	file << now << "," << data.str() << std::endl;
	file.close();
}

template <typename T>
void ExecutionHistoricalDataServiceConnector<T>::Subscribe(std::string filePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void StreamingHistoricalDataServiceConnector<T>::Publish(PriceStream<T>& data)
{
	// write to local txt file
	std::ofstream file;

	ptime now = microsec_clock::local_time();
	// append to original text
	file = std::ofstream(filePath, std::ofstream::out | std::ofstream::app);
	file << now << "," << data.str() << std::endl;
	file.close();
}

template <typename T>
void StreamingHistoricalDataServiceConnector<T>::Subscribe(std::string filePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void InquiryHistoricalDataServiceConnector<T>::Publish(Inquiry<T>& data)
{
	// write to local txt file
	std::ofstream file;

	ptime now = microsec_clock::local_time();
	// append to original text
	file = std::ofstream(filePath, std::ofstream::out | std::ofstream::app);
	file << now << "," << data.str() << std::endl;
	file.close();
}

template <typename T>
void InquiryHistoricalDataServiceConnector<T>::Subscribe(std::string filePath)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////




#endif