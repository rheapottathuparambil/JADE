#ifndef __JAVA_H__
#define __JAVA_H__
#include "product.h"
#include <vector>
#include <ostream>
#include <sstream>

enum Darkness {Blonde, Light, Medium, Dark, Extra_dark};
const std::vector<std::string> darkness_to_string = {"Blonde", "Light", "Medium", "Dark", "Extra Dark"};

enum Shot {None, Chocolate, Vanilla, Peppermint, Hazelnut};
const std::vector<std::string> shot_to_string = {"none", "chocolate", "vanilla", "peppermint", "hazelnut"};

class Java : public Product 
{
  
  protected:
    Darkness _darkness;
    std::vector<Shot> _shots; 
 
  public:
    Java(std::string name, double price, double cost, Darkness darkness);
    Java(std::istream& ist);
    void add_shot(Shot shot);
    std::string to_string() override;
    std::string to_string_file() override;
};
#endif
    
