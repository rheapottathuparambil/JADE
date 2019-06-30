#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__
#include <string>
#include <ostream>
#include <istream>
#include <vector>

class Customer 
{
  private:
    std::string _customer;
    std::string _customer_phone;
 
  public:
    Customer(std::string customer, std::string customer_phone);
    Customer();
    Customer(std::istream& ist);
    void save(std::ostream& ost);
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& ost, const Customer& customer);
  
};
#endif
