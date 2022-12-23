/**
 * riskservice.hpp
 * Defines the data types and Service for fixed income risk.
 *
 * @author Breman Thuraisingham
 */
#ifndef RISK_SERVICE_HPP
#define RISK_SERVICE_HPP

#include "soa.hpp"
#include "positionservice.hpp"
#include <string>
#include <sstream>

 /**
  * PV01 risk.
  * Type T is the product type.
  */
template<typename T>
class PV01
{

public:

    // ctor for a PV01 value
    PV01(const T& _product, double _pv01, long _quantity);

    // Get the product on this PV01 value
    const T& GetProduct() const;

    // Get the PV01 value
    double GetPV01() const;

    // Get the quantity that this risk value is associated with
    long GetQuantity() const;

    // Add quantity
    void AddQuantity(long _quantity);


    // return string form
    std::string str() const;

private:
    T product;
    double pv01;
    long quantity;

};

/**
 * A bucket sector to bucket a group of securities.
 * We can then aggregate bucketed risk to this bucket.
 * Type T is the product type.
 */
template<typename T>
class BucketedSector
{

public:

    // ctor for a bucket sector
    BucketedSector(const vector<T>& _products, string _name);

    // Get the products associated with this bucket
    const vector<T>& GetProducts() const;

    // Get the name of the bucket
    const string& GetName() const;

    // same as GetName()
    std::string GetProductId() const;

private:
  vector<T> products;
  string name;

};

/**
 * Risk Service to vend out risk for a particular security and across a risk bucketed sector.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class RiskService : public Service<string,PV01 <T> >
{

public:

  // Add a position that the service will risk
  virtual void AddPosition(Position<T> &position) = 0;

  // Get the bucketed risk for the bucket sector
  virtual const PV01< BucketedSector<T> > GetBucketedRisk(const BucketedSector<T> &sector) const = 0;

};

template<typename T>
PV01<T>::PV01(const T &_product, double _pv01, long _quantity) :
  product(_product)
{
  pv01 = _pv01;
  quantity = _quantity;
}


// Get the product on this PV01 value
template<typename T>
const T& PV01<T>::GetProduct() const
{
    return product;
}

// Get the PV01 value
template<typename T>
double PV01<T>::GetPV01() const
{
    return pv01;
}

// Get the quantity that this risk value is associated with
template<typename T>
long PV01<T>::GetQuantity() const
{
    return quantity;
}

// Get the quantity that this risk value is associated with
template<typename T>
void PV01<T>::AddQuantity(long _quantity)
{
    quantity += _quantity;
}

// return string form
template<typename T>
std::string PV01<T>::str() const
{
    std::stringstream ss;
    std::string id = product.GetProductId();
    ss << id << ",(PV01)" << pv01 << "," << quantity;
    return ss.str();
}

template<typename T>
BucketedSector<T>::BucketedSector(const vector<T>& _products, string _name) :
  products(_products)
{
  name = _name;
}

template<typename T>
const vector<T>& BucketedSector<T>::GetProducts() const
{
  return products;
}

template<typename T>
const string& BucketedSector<T>::GetName() const
{
  return name;
}

template<typename T>
std::string BucketedSector<T>::GetProductId() const
{
    return name;
}

#endif
