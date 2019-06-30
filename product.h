#ifndef __PRODUCT_H__
#define __PRODUCT_H__
#include <string>
#include <ostream>

class Product 
{
    
  protected:
    std::string _name;
    double _price;
    double _cost;

  public:
    Product(std::string name, double price, double cost);
    Product();
    double profit() const;
    std::string name();
    virtual std::string to_string();
    virtual std::string to_string_file();
};
#endif
