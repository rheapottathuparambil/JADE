#include "order.h"
#include <stdexcept>

int Order::_next_order_number = 0;

Order::Order() : _order_number{_next_order_number++}, _is_paid{false}, _is_filled{false}, _is_discarded{false} { }

int Order::order_number() const 
{
    return _order_number;
}
void Order::add_product(Product* product) 
{
    _products.push_back(product);
}

bool Order::paid() const 
{
    return (!_is_discarded && _is_paid);
}

void Order::pay() 
{
    if (_is_discarded) throw std::runtime_error{"Attempt to pay discarded order " + std::to_string(_order_number)};
    if (_is_paid) throw std::runtime_error{"Attempt to pay paid order " + std::to_string(_order_number)};
    _is_paid = true;
}

double Order::profit() const 
{
    double value = 0.0;
    for (auto p : _products) value += p->profit();
    return value;
}

bool Order::filled() const 
{
    return (!_is_discarded && _is_filled);
}

void Order::fill() 
{
    if (_is_discarded) throw std::runtime_error{"Attempt to fill discarded order " + std::to_string(_order_number)};
    if (_is_filled) throw std::runtime_error{"Attempt to fill filled order " + std::to_string(_order_number)};
    _is_filled = true;
}

bool Order::discarded() const 
{
    return _is_discarded;
}

void Order::discard() 
{
    if (_is_discarded) throw std::runtime_error{"Attempt to discard discarded order " + std::to_string(_order_number)};
    if (completed()) throw std::runtime_error{"Attempt to discard completed order " + std::to_string(_order_number)};
    _is_discarded = true;
}

bool Order::completed() const 
{
    return (paid() && filled());
}

bool Order::pending() const 
{
    return !(completed() || discarded());
}

std::ostream& operator<<(std::ostream& ost, const Order& order) 
{
    ost << "Order #" << order._order_number;
    if (order.discarded()) 
    {
        ost << " (discarded):";
    } 
    else if (order.filled()) 
    {
        if (order.paid()) ost << " (completed):";
        else ost << " (filled)";
    } 
    else 
    {
        if (order.paid()) ost << " (paid):";
        else ost << " (pending):";
    }
    std::string separator = "\n  ";
    for (auto p : order._products) 
    {
        ost << separator << p->to_string();
    }
    return ost;
}

bool operator<(const Order& lhs, const Order& rhs) 
{
    return lhs.order_number() < rhs.order_number();
}

