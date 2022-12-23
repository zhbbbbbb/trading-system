#ifndef BOND_EXECUTION_SERVICE_CONNECTOR_HPP
#define BOND_EXECUTION_SERVICE_CONNECTOR_HPP

#include <iostream>
#include "soa.hpp"
#include "products.hpp"
#include "executionservice.hpp"
#include "utility.hpp"

class BondExecutionServiceConnector : public Connector<ExecutionOrder<Bond>>
{
public:

	virtual void Publish(ExecutionOrder<Bond>& executionOrder);

	virtual void Subscribe(std::string filePath);
private:
	static int i;
};

int BondExecutionServiceConnector::i = 0;

void BondExecutionServiceConnector::Publish(ExecutionOrder<Bond>& executionOrder)
{// print the ExecutionOrder when  BondStreamingService receives them

	//std::cout << (++i) << "th Execution Order:" << std::endl;
	//std::cout << executionOrder.str() << std::endl;

	// print only every 10000 orders
	if (!(++i % 1000))
	{
		std::cout << i << "th Execution Order:" << std::endl;
		std::cout << executionOrder.str() << std::endl;
	}
}

void BondExecutionServiceConnector::Subscribe(std::string filePath)
{

}













#endif