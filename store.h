#ifndef __STORE_H__
#define __STORE_H__
#include "product.h"
#include "customer.h"
#include "order.h"
#include "java.h"
#include "donut.h"
#include <vector>
#include <map>

class Store 
{
  public:
    Store(std::string store_name);
    Store(std::istream& ist);
    std::string name(); 
    double cash(); 

    void add_product(Product* product);
    int number_of_products(); 
    std::string product_to_string(int product);
    Product* get_product(int product);

    void add_customer(Customer* customer); 
    int number_of_customers(); 
    std::string customer_to_string(int customer); 
    void save(std::ostream& ost);
    friend std::ostream& operator<<(std::ostream& ost, Store& store); 

    void place_order(Order order, int customer);
    int number_of_orders(); 
    std::string order_to_string(int order_number); 

    void pay_order(int order_number); 
    bool order_is_paid(int order_number); 
    void fill_order(int order_number); 
    bool order_is_filled(int order_number); 
    void discard_order(int order_number); 
    bool order_is_discarded(int order_number);  

    bool order_is_completed(int order_number);
    bool order_is_pending(int order_number); 

    friend std::ostream& operator<<(std::ostream& ost, Store& store); 
  
  private:
    std::string _name;
    std::vector<Product*> _products;
    std::vector<Customer*> _customers;
    double _cash_register;
    typedef std::pair<const Order, Customer> Order_pair;
    typedef std::map<const Order, Customer> Orders;
    Orders _orders;
    Order_pair& find_order_pair(int order_number);
};
#endif