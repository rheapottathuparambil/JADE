#include "store.h"
#include "to_string.h"
#include <sstream>
#include <stdexcept>

Store::Store(std::string store_name) : _name{store_name}, _cash_register{1000.0} { }
std::string Store::name() 
{
    return _name;
}

double Store::cash() 
{
    return _cash_register;
}

Store::Store(std::istream& ist)
{
    std::string str;
    while(std::getline(ist,str))
    {
        if(str == "CUSTOMER")
        {
            Customer *c = new Customer{ist};
            _customers.push_back(c);
        }

        else if(str == "PRODUCT")
        {
            std::getline(ist,str);
            if(str == "0")
            {
                Java *j = new Java{ist};
                 _products.push_back(j);
            }
            else 
            { 
                Donut *d = new Donut{ist};
                _products.push_back(d);
            }
        }
    }
}

void Store::add_product(Product* product) 
{
    _products.push_back(product);
}

int Store::number_of_products() 
{
    return _products.size();
}

std::string Store::product_to_string(int product) 
{
    return _products[product]->to_string();
}

void Store::add_customer(Customer* customer) 
{
    _customers.push_back(customer);
}

int Store::number_of_customers() 
{
    return _customers.size();
}

Product* Store::get_product(int product) 
{
    return _products[product];
}

std::string Store::customer_to_string(int customer) 
{
    std::ostringstream oss;
    oss << *_customers[customer];
    return oss.str();
}

void Store::save(std::ostream& ost)
{
    for(auto c: _customers)
    {
        ost<<"CUSTOMER"<<std::endl;
        c->save(ost);
    }
    int i;
    for(auto p: _products)
    {
        ost<<"PRODUCT"<<std::endl;
        ost<<p->to_string_file()<<std::endl;
    }
}

Store::Order_pair& Store::find_order_pair(int order_number) 
{
    for (Order_pair& o : _orders) if (o.first.order_number() == order_number) return o;
    throw std::runtime_error{"Order " + std::to_string(order_number) + " not found"};
} 

void Store::place_order(Order order, int customer) 
{
    _orders[order] = *_customers[customer];
} 

int Store::number_of_orders() 
{
    return _orders.size(); 
}

std::string Store::order_to_string(int order_number) 
{
    Order_pair& op = find_order_pair(order_number);
    return to_string(op.first) + "\n" + to_string(op.second);
} 

void Store::pay_order(int order_number) 
{
    Order_pair& p = find_order_pair(order_number);
    Order o = p.first;
    Customer c = p.second;
    _orders.erase(p.first);
    o.pay();
    _orders[o] = p.second;
    _cash_register += o.profit();
}  

bool Store::order_is_paid(int order_number) 
{
    Order_pair& p = find_order_pair(order_number);
    return p.first.paid();
}  

void Store::fill_order(int order_number) 
{
    Order_pair& p = find_order_pair(order_number);
    Order o = p.first;
    Customer c = p.second;
    _orders.erase(p.first);
    o.fill();
    _orders[o] = p.second;
}  

bool Store::order_is_filled(int order_number) 
{
    Order_pair& p = find_order_pair(order_number);
    return p.first.filled();
}  

void Store::discard_order(int order_number) 
{
    Order_pair& p = find_order_pair(order_number);
    Order o = p.first;
    Customer c = p.second;
    if (o.paid()) _cash_register -= o.profit(); 
    _orders.erase(p.first);
    o.discard();
    _orders[o] = p.second;
} 

bool Store::order_is_discarded(int order_number) 
{
    Order_pair& p = find_order_pair(order_number);
    return p.first.discarded();
} 

bool Store::order_is_pending(int order_number) 
{
    Order_pair& p = find_order_pair(order_number);
    return p.first.pending();
} 

bool Store::order_is_completed(int order_number) 
{
    Order_pair& p = find_order_pair(order_number);
    return p.first.completed();
}

std::ostream& operator<<(std::ostream& ost, Store& store) 
{
    ost << "Store " << store._name << std::endl << std::endl;
    ost << "Products: " << std::endl;
    for (auto p : store._products) ost << "  " << p->to_string() << std::endl;
    return ost;
}

