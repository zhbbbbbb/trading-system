/**
 * inquiryservice.hpp
 * Defines the data types and Service for customer inquiries.
 *
 * @author Breman Thuraisingham
 */
#ifndef INQUIRY_SERVICE_HPP
#define INQUIRY_SERVICE_HPP

#include <string>
#include <sstream>
#include "soa.hpp"
#include "tradebookingservice.hpp"

// Various inquiry states
enum InquiryState { RECEIVED, QUOTED, DONE, REJECTED, CUSTOMER_REJECTED };

std::string InquiryStateToString(InquiryState inquiryState)
{
    std::string s;
    switch (inquiryState)
    {
    case RECEIVED:
        s = "RECEIVED"; break;
    case QUOTED:
        s = "QUOTED"; break;
    case DONE:
        s = "DONE"; break;
    case REJECTED:
        s = "REJECTED"; break;
    case CUSTOMER_REJECTED:
        s = "CUSTOMER_REJECTED"; break;
    default:
        std::cerr << "Invalid Inquiry State." << std::endl; break;
    }
    return s;
}


/**
 * Inquiry object modeling a customer inquiry from a client.
 * Type T is the product type.
 */
template<typename T>
class Inquiry
{

public:

  // ctor for an inquiry
  Inquiry(string _inquiryId, const T &_product, Side _side, long _quantity, double _price, InquiryState _state);

  // Get the inquiry ID
  const string& GetInquiryId() const;

  // Get the product
  const T& GetProduct() const;

  // Get the side on the inquiry
  Side GetSide() const;

  // Get the quantity that the client is inquiring for
  long GetQuantity() const;

  // Get the price that we have responded back with
  double GetPrice() const;

  // Get the current state on the inquiry
  InquiryState GetState() const;

  // Set the current price on the inquiry
  void SetPrice(double _price);

  // Set the current state on the inquiry
  void SetState(InquiryState _state);

  std::string str() const;

private:
  string inquiryId;
  T product;
  Side side;
  long quantity;
  double price;
  InquiryState state;

};

/**
 * Service for customer inquirry objects.
 * Keyed on inquiry identifier (NOTE: this is NOT a product identifier since each inquiry must be unique).
 * Type T is the product type.
 */
template<typename T>
class InquiryService : public Service<string,Inquiry <T> >
{

public:

  // Send a quote back to the client
  virtual void SendQuote(const string &inquiryId, double price) = 0;

  // Reject an inquiry from the client
  virtual void RejectInquiry(const string &inquiryId) = 0;

};

template<typename T>
Inquiry<T>::Inquiry(string _inquiryId, const T &_product, Side _side, long _quantity, double _price, InquiryState _state) :
  product(_product)
{
  inquiryId = _inquiryId;
  side = _side;
  quantity = _quantity;
  price = _price;
  state = _state;
}

template<typename T>
const string& Inquiry<T>::GetInquiryId() const
{
  return inquiryId;
}

template<typename T>
const T& Inquiry<T>::GetProduct() const
{
  return product;
}

template<typename T>
Side Inquiry<T>::GetSide() const
{
  return side;
}

template<typename T>
long Inquiry<T>::GetQuantity() const
{
  return quantity;
}

template<typename T>
double Inquiry<T>::GetPrice() const
{
  return price;
}

template<typename T>
InquiryState Inquiry<T>::GetState() const
{
  return state;
}

template<typename T>
void Inquiry<T>::SetPrice(double _price)
{
    price = _price;
}

template<typename T>
void Inquiry<T>::SetState(InquiryState _state)
{
    state = _state;
}

template<typename T>
std::string Inquiry<T>::str() const
{
    std::stringstream ss;
    std::string id = product.GetProductId();
    ss << inquiryId << "," << id << "," << InquiryStateToString(state) << ","
        << "," << SideToString(side) << "," << price << "," << quantity;
    return ss.str();
}



#endif
