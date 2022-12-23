/**
 * streamingservice.hpp
 * Defines the data types and Service for price streams.
 *
 * @author Breman Thuraisingham
 */
#ifndef STREAMING_SERVICE_HPP
#define STREAMING_SERVICE_HPP

#include <string>
#include <sstream>
#include "soa.hpp"
#include "marketdataservice.hpp"
#include "pricingservice.hpp"

/**
 * A price stream order with price and quantity (visible and hidden)
 */
class PriceStreamOrder
{

public:

  // ctor for an order
  PriceStreamOrder(double _price, long _visibleQuantity, long _hiddenQuantity, PricingSide _side);

  // The side on this order
  PricingSide GetSide() const;

  // Get the price on this order
  double GetPrice() const;

  // Get the visible quantity on this order
  long GetVisibleQuantity() const;

  // Get the hidden quantity on this order
  long GetHiddenQuantity() const;

  std::string str() const;

private:
  double price;
  long visibleQuantity;
  long hiddenQuantity;
  PricingSide side;

};

/**
 * Price Stream with a two-way market.
 * Type T is the product type.
 */
template<typename T>
class PriceStream
{

public:

  // ctor
  PriceStream(const T &_product, const PriceStreamOrder &_bidOrder, const PriceStreamOrder &_offerOrder);

  // Get the product
  const T& GetProduct() const;

  // Get the bid order
  const PriceStreamOrder& GetBidOrder() const;

  // Get the offer order
  const PriceStreamOrder& GetOfferOrder() const;

  std::string str() const;

private:
  T product;
  PriceStreamOrder bidOrder;
  PriceStreamOrder offerOrder;

};

/**
 * Streaming service to publish two-way prices.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class StreamingService : public Service<string,PriceStream <T> >
{

public:

  // Publish two-way prices
  virtual void PublishPrice(PriceStream<T>& priceStream) = 0;

};


template <typename T>
class AlgoStream
{
public:
    // param ctor
    AlgoStream(PriceStream<T> _priceStream);

    // get the price stream
    PriceStream<T> GetPriceStream() const;

    // update price stream
    void UpdatePriceStream(const Price<T>& price);

private:
    PriceStream<T> priceStream;
    static int numId;
};


template<typename T>
class AlgoStreamingService : public Service<string, AlgoStream<T>>
{

public:
    // when listener gets a new Price
    virtual void AddPrice(const Price<T>& price) = 0;

};



PriceStreamOrder::PriceStreamOrder(double _price, long _visibleQuantity, long _hiddenQuantity, PricingSide _side)
{
  price = _price;
  visibleQuantity = _visibleQuantity;
  hiddenQuantity = _hiddenQuantity;
  side = _side;
}

double PriceStreamOrder::GetPrice() const
{
  return price;
}

PricingSide PriceStreamOrder::GetSide() const
{
  return side;
}

long PriceStreamOrder::GetVisibleQuantity() const
{
  return visibleQuantity;
}

long PriceStreamOrder::GetHiddenQuantity() const
{
  return hiddenQuantity;
}

std::string PriceStreamOrder::str() const
{
    std::stringstream ss;
    ss << PricingSideToString(side) << "," << price << ",V" << visibleQuantity << ",H" << hiddenQuantity;
    return ss.str();
}


template<typename T>
PriceStream<T>::PriceStream(const T &_product, const PriceStreamOrder &_bidOrder, const PriceStreamOrder &_offerOrder) :
  product(_product), bidOrder(_bidOrder), offerOrder(_offerOrder)
{
}

template<typename T>
const T& PriceStream<T>::GetProduct() const
{
  return product;
}

template<typename T>
const PriceStreamOrder& PriceStream<T>::GetBidOrder() const
{
  return bidOrder;
}

template<typename T>
const PriceStreamOrder& PriceStream<T>::GetOfferOrder() const
{
  return offerOrder;
}

template<typename T>
std::string PriceStream<T>::str() const
{
    std::stringstream ss;
    std::string id = product.GetProductId();
    ss << id << "," << "{Bid:" << bidOrder.str() << "},{Offer:" << offerOrder.str() << "}";
    return ss.str();
}

template <typename T>
int AlgoStream<T>::numId = 0;

// param ctor
template <typename T>
AlgoStream<T>::AlgoStream(PriceStream<T> _priceStream) : priceStream(_priceStream)
{

}

// get the price stream
template <typename T>
PriceStream<T> AlgoStream<T>::GetPriceStream() const
{
    return priceStream;
}

// update price stream
template <typename T>
void AlgoStream<T>::UpdatePriceStream(const Price<T>& price)
{
    T product = price.GetProduct();

    // check if it's the same bond
    if (priceStream.GetProduct().GetProductId() != product.GetProductId()) return;

    double midPrice = price.GetMid();
    double spread = price.GetBidOfferSpread();
    double bidPrice = midPrice - spread * 0.5;
    double offerPrice = midPrice + spread * 0.5;

    long bidVisibleQuantity = (numId % 2 ? 1000000 : 2000000);
    long offerVisibleQuantity = (numId % 2 ? 1000000 : 2000000);
    long bidHiddenQuantity = 2 * bidVisibleQuantity;
    long offerHiddenQuantity = 2 * offerVisibleQuantity;
    PriceStreamOrder bidOrder(bidPrice, bidVisibleQuantity, bidHiddenQuantity, BID);
    PriceStreamOrder offerOrder(offerPrice, offerVisibleQuantity, offerHiddenQuantity, OFFER);
    priceStream = PriceStream<T>(product, bidOrder, offerOrder);
    ++numId;

}




#endif
