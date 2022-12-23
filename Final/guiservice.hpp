#ifndef GUI_SERVICE_HPP
#define GUI_SERVICE_HPP


#include "products.hpp"
#include "pricingservice.hpp"
#include "soa.hpp"
#include <string>

template <typename T>
class GUIService : public Service<std::string, Price<T>>
{

};









#endif