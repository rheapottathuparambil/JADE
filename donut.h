#ifndef __DONUT_H__
#define __DONUT_H__
#include "product.h"
#include <vector>
#include <ostream>
#include <sstream>

enum Frosting {Unfrosted, Chocolate_top, Vanilla_top, Pink_top};
const std::vector<std::string> frosting_string = {"unfrosted", "chocolate", "vanilla", "pink"};

enum Filling {Unfilled, Creme, Bavarian, Strawberry};
const std::vector<std::string> filling_string = {"unfilled", "creme", "Bavarian", "strawberry"};

class Donut : public Product 
{
  protected:
    Frosting _frosting;
    bool _sprinkles;
    Filling _filling;
  
  public:
    Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling);
    Donut(std::istream & ist);
    std::string to_string() override;
    std::string to_string_file() override; 
    friend std::ostream& operator<<(std::ostream& ost, Product& p); 
};

#endif
