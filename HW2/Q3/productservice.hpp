/**
 * productservice.hpp defines Bond and IRSwap ProductServices
 */

#include <iostream>
#include <map>
#include <vector>
#include "products.hpp"
#include "soa.hpp"

/**
 * Bond Product Service to own reference data over a set of bond securities.
 * Key is the productId string, value is a Bond.
 */
class BondProductService : public Service<string,Bond>
{

public:
  // BondProductService ctor
  BondProductService();

  // Return the bond data for a particular bond product identifier
  Bond& GetData(string productId);

  // Add a bond to the service (convenience method)
  void Add(Bond &bond);

  // Get all Bonds with the specified ticker
  std::vector<Bond> GetBonds(string& _ticker);

private:
  map<string,Bond> bondMap; // cache of bond products

};
/**
 * Interest Rate Swap Product Service to own reference data over a set of IR Swap products
 * Key is the productId string, value is a IRSwap.
 */
class IRSwapProductService : public Service<string,IRSwap>
{
public:
  // IRSwapProductService ctor
  IRSwapProductService();

  // Return the IR Swap data for a particular bond product identifier
  IRSwap& GetData(string productId);

  // Add a bond to the service (convenience method)
  void Add(IRSwap &swap);

  // Get all Swaps with the specified fixed leg day count convention
  vector<IRSwap> GetSwaps(DayCountConvention _fixedLegDayCountConvention);

  // Get all Swaps with the specified fixed leg payment frequency
  vector<IRSwap> GetSwaps(PaymentFrequency _fixedLegPaymentFrequency);

  // Get all Swaps with the specified floating index
  vector<IRSwap> GetSwaps(FloatingIndex _floatingIndex);

  // Get all Swaps with a term in years greater than the specified value
  vector<IRSwap> GetSwapsGreaterThan(int _termYears);

  // Get all Swaps with a term in years less than the specified value
  vector<IRSwap> GetSwapsLessThan(int _termYears);

  // Get all Swaps with the specified swap type
  vector<IRSwap> GetSwaps(SwapType _swapType);

  // Get all Swaps with the specified swap leg type
  vector<IRSwap> GetSwaps(SwapLegType _swapLegType);


private:
  map<string,IRSwap> swapMap; // cache of IR Swap products

};

BondProductService::BondProductService()
{
  bondMap = map<string,Bond>();
}

Bond& BondProductService::GetData(string productId)
{
  return bondMap[productId];
}

void BondProductService::Add(Bond &bond)
{
  bondMap.insert(pair<string,Bond>(bond.GetProductId(), bond));
}


// Get all Bonds with the specified ticker
std::vector<Bond> BondProductService::GetBonds(string& _ticker)
{
    std::vector<Bond> instances;
    for (auto bond_pair : bondMap)
    {
        if (bond_pair.second.GetTicker() == _ticker)
        {
            instances.push_back(bond_pair.second);
        }
    }    
    return instances;
}

IRSwapProductService::IRSwapProductService()
{
  swapMap = map<string,IRSwap>();
}

IRSwap& IRSwapProductService::GetData(string productId)
{
  return swapMap[productId];
}

void IRSwapProductService::Add(IRSwap &swap)
{
  swapMap.insert(pair<string,IRSwap>(swap.GetProductId(), swap));
}


// Get all Swaps with the specified fixed leg day count convention
std::vector<IRSwap> IRSwapProductService::GetSwaps(DayCountConvention _fixedLegDayCountConvention)
{
    std::vector<IRSwap> instances;
    for (auto swap_pair : swapMap)
    {
        if (swap_pair.second.GetFixedLegDayCountConvention() == _fixedLegDayCountConvention)
        {
            instances.push_back(swap_pair.second);
        }
    }
    return instances;
}

// Get all Swaps with the specified fixed leg payment frequency
std::vector<IRSwap> IRSwapProductService::GetSwaps(PaymentFrequency _fixedLegPaymentFrequency)
{
    std::vector<IRSwap> instances;
    for (auto swap_pair : swapMap)
    {
        if (swap_pair.second.GetFixedLegPaymentFrequency() == _fixedLegPaymentFrequency)
        {
            instances.push_back(swap_pair.second);
        }
    }
    return instances;
}

// Get all Swaps with the specified floating index
std::vector<IRSwap> IRSwapProductService::GetSwaps(FloatingIndex _floatingIndex)
{
    std::vector<IRSwap> instances;
    for (auto swap_pair : swapMap)
    {
        if (swap_pair.second.GetFloatingIndex() == _floatingIndex)
        {
            instances.push_back(swap_pair.second);
        }
    }
    return instances;
}

// Get all Swaps with a term in years greater than the specified value
std::vector<IRSwap> IRSwapProductService::GetSwapsGreaterThan(int _termYears)
{
    std::vector<IRSwap> instances;
    for (auto swap_pair : swapMap)
    {
        if (swap_pair.second.GetTermYears() > _termYears)
        {
            instances.push_back(swap_pair.second);
        }
    }
    return instances;
}

// Get all Swaps with a term in years less than the specified value
std::vector<IRSwap> IRSwapProductService::GetSwapsLessThan(int _termYears)
{
    std::vector<IRSwap> instances;
    for (auto swap_pair : swapMap)
    {
        if (swap_pair.second.GetTermYears() < _termYears)
        {
            instances.push_back(swap_pair.second);
        }
    }
    return instances;
}

// Get all Swaps with the specified swap type
std::vector<IRSwap> IRSwapProductService::GetSwaps(SwapType _swapType)
{
    std::vector<IRSwap> instances;
    for (auto swap_pair : swapMap)
    {
        if (swap_pair.second.GetSwapType() == _swapType)
        {
            instances.push_back(swap_pair.second);
        }
    }
    return instances;
}

// Get all Swaps with the specified swap leg type
std::vector<IRSwap> IRSwapProductService::GetSwaps(SwapLegType _swapLegType)
{
    std::vector<IRSwap> instances;
    for (auto swap_pair : swapMap)
    {
        if (swap_pair.second.GetSwapLegType() == _swapLegType)
        {
            instances.push_back(swap_pair.second);
        }
    }
    return instances;
}
