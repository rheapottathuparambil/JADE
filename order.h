#pragma once
#include "product.h"
#include <vector>

class Order {
  public:
    Order();
    int order_number() const;
    void add_product(Product* product);
    bool paid() const;
    void pay();
    bool filled() const;
    void fill();
    bool discarded() const;
    void discard();
    bool pending() const;
    bool completed() const;
    double profit() const;
    friend std::ostream& operator<<(std::ostream& ost, const Order& order);
  protected:
    std::vector<Product*> _products;
  private:
    static int _next_order_number;
    int _order_number; 
    bool _is_paid;
    bool _is_filled;
    bool _is_discarded;
};

bool operator<(const Order& lhs, const Order& rhs);
