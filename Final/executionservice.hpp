/**
 * executionservice.hpp
 * Defines the data types and Service for executions.
 *
 * @author Breman Thuraisingham
 */
#ifndef EXECUTION_SERVICE_HPP
#define EXECUTION_SERVICE_HPP

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "soa.hpp"
#include "marketdataservice.hpp"

enum OrderType { FOK, IOC, MARKET, LIMIT, STOP };

std::string OrderTypeToString(OrderType orderType)
{
    std::string result;
    switch (orderType)
    {
    case FOK:
        result = "FOK"; break;
    case IOC:
        result = "IOC"; break;
    case MARKET:
        result = "MARKET"; break;
    case LIMIT:
        result = "LIMIT"; break;
    case STOP:
        result = "STOP"; break;
    default:
        result = ""; break;
    }
    return result;
}

enum Market { BROKERTEC, ESPEED, CME };

/**
 * An execution order that can be placed on an exchange.
 * Type T is the product type.
 */
template<typename T>
class ExecutionOrder
{

public:

  // ctor for an order
  ExecutionOrder(const T &_product, PricingSide _side, string _orderId, OrderType _orderType, double _price, long _visibleQuantity, long _hiddenQuantity, string _parentOrderId, bool _isChildOrder);

  // Get the product
  const T& GetProduct() const;

  PricingSide GetPricingSide() const;

  // Get the order ID
  const string& GetOrderId() const;

  // Get the order type on this order
  OrderType GetOrderType() const;

  // Get the price on this order
  double GetPrice() const;

  // Get the visible quantity on this order
  long GetVisibleQuantity() const;

  // Get the hidden quantity
  long GetHiddenQuantity() const;

  // Get the parent order ID
  const string& GetParentOrderId() const;

  // Is child order?
  bool IsChildOrder() const;

  std::string str() const;

private:
  T product;
  PricingSide side;
  string orderId;
  OrderType orderType;
  double price;
  long visibleQuantity;
  long hiddenQuantity;
  string parentOrderId;
  bool isChildOrder;

};

/**
 * Service for executing orders on an exchange.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class ExecutionService : public Service<string,ExecutionOrder <T> >
{

public:

  // Execute an order on a market
  virtual void ExecuteOrder(ExecutionOrder<T>& order, Market market) = 0;

};

template <typename T>
class AlgoExecution
{
public:
    // param ctor
    AlgoExecution(ExecutionOrder<T> _executionOrder);
    AlgoExecution(const OrderBook<T>& orderBook);

    // get the execution order
    ExecutionOrder<T> GetExecutionOrder() const;

    // run algorithm on the new orderbook
    void UpdateExecutionOrder(const OrderBook<T>& orderBook);

private:
    ExecutionOrder<T> executionOrder;
    static int numId;
};

template<typename T>
class AlgoExecutionService : public Service<string, AlgoExecution<T>>
{

public:
    // update execution order when given an order book
    virtual void AddOrderBook(const OrderBook<T>& orderBook) = 0;

};

template<typename T>
ExecutionOrder<T>::ExecutionOrder(const T &_product, PricingSide _side, string _orderId, OrderType _orderType, double _price, long _visibleQuantity, long _hiddenQuantity, string _parentOrderId, bool _isChildOrder) :
  product(_product)
{
  side = _side;
  orderId = _orderId;
  orderType = _orderType;
  price = _price;
  visibleQuantity = _visibleQuantity;
  hiddenQuantity = _hiddenQuantity;
  parentOrderId = _parentOrderId;
  isChildOrder = _isChildOrder;
}

template<typename T>
const T& ExecutionOrder<T>::GetProduct() const
{
  return product;
}

template<typename T>
PricingSide ExecutionOrder<T>::GetPricingSide() const
{
    return side;
}

template<typename T>
const string& ExecutionOrder<T>::GetOrderId() const
{
  return orderId;
}

template<typename T>
OrderType ExecutionOrder<T>::GetOrderType() const
{
  return orderType;
}

template<typename T>
double ExecutionOrder<T>::GetPrice() const
{
  return price;
}

template<typename T>
long ExecutionOrder<T>::GetVisibleQuantity() const
{
  return visibleQuantity;
}

template<typename T>
long ExecutionOrder<T>::GetHiddenQuantity() const
{
  return hiddenQuantity;
}

template<typename T>
const string& ExecutionOrder<T>::GetParentOrderId() const
{
  return parentOrderId;
}

template<typename T>
bool ExecutionOrder<T>::IsChildOrder() const
{
  return isChildOrder;
}

// string form of ExecutionOrder
template<typename T>
std::string ExecutionOrder<T>::str() const
{
    std::stringstream ss;
    std::string id = product.GetProductId();

    ss << id << "," << PricingSideToString(side) << "," << OrderTypeToString(orderType) << "," << price << ",V" << visibleQuantity << ",H" << hiddenQuantity
        << "," << (isChildOrder? "ISCHILD":"NOTCHILD") << "," << (isChildOrder ? parentOrderId : "N/A");

    return ss.str();
}



template<typename T>
int AlgoExecution<T>::numId = 0;

// param ctor
template<typename T>
AlgoExecution<T>::AlgoExecution(ExecutionOrder<T> _executionOrder) : executionOrder(_executionOrder)
{

}


// param ctor by orderbook
template<typename T>
AlgoExecution<T>::AlgoExecution(const OrderBook<T>& orderBook) :
    executionOrder(ExecutionOrder<T>(orderBook.GetProduct(), BID, "NullOrderID", LIMIT, 0.0, 0, 0, "NullParentOrder", false))
{
    // initialize a meaningless ExecutionOrder when ctor param is an orderBook
    // important to record the product
}

// get the execution order
template<typename T>
ExecutionOrder<T> AlgoExecution<T>::GetExecutionOrder() const
{
    return executionOrder;
}



// run algorithm, same as orderBook param ctor
template<typename T>
void AlgoExecution<T>::UpdateExecutionOrder(const OrderBook<T>& orderBook)
{
    T product = orderBook.GetProduct();

    // check if it's the same bond
    if (executionOrder.GetProduct().GetProductId() != product.GetProductId()) return;

    std::string prodId = product.GetProductId();

    std::string orderId = "AlgoOrder" + std::to_string(numId);
    PricingSide side = (numId%2?BID:OFFER);
    OrderType orderType;
    switch (numId % 5)
    {
    case 0:
        orderType = FOK; break;
    case 1:
        orderType = IOC; break;
    case 2:
        orderType = MARKET; break;
    case 3:
        orderType = LIMIT; break;
    case 4:
        orderType = STOP; break;
    default:
        orderType = FOK;
    }
    // crossing the spread
    std::vector<Order> bidOrders = orderBook.GetBidStack();
    std::vector<Order> offerOrders = orderBook.GetOfferStack();
    // order to counter
    Order order = (side == BID ? *(std::max_element(offerOrders.begin(), offerOrders.end())) : *(std::max_element(bidOrders.begin(), bidOrders.end())));
    double price = order.GetPrice();

    // quantity
    long visibleQuantity = order.GetQuantity();
    long hiddenQuantity = 2 * visibleQuantity;

    // parent order
    std::string parentOrderId = "ParentAlgoOrder" + std::to_string(numId);
    bool isChildOrder = true;

    // update execution order
    executionOrder = ExecutionOrder<T>(product, side, orderId, orderType, price, visibleQuantity, hiddenQuantity, parentOrderId, isChildOrder);

    // update id number
    ++numId;
    //std::cout << "ExecutionOrder numId: " << numId << std::endl;
}


#endif
