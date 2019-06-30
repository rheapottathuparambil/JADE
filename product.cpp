#include "product.h"
#include <sstream>
#include <iostream>
#include <iomanip>

Product::Product(std::string name, double price, double cost) : _name{name}, _price{price}, _cost{cost} { }
Product::Product() {}
std::string Product::name() 
{
    return _name;
}

std::string Product::to_string() 
{
    std::ostringstream oss;
    oss << _name << std::fixed << std::setprecision(2) << " ($" << _price << " / $" << _cost << ')';
    return oss.str();
}

std::string Product::to_string_file() 
{
    std::ostringstream oss;
    oss << _name << std::endl << _price << std::endl<< _cost << std::endl;
    return oss.str();
}

double Product::profit() const 
{
    return _price - _cost;
}


