#include "donut.h"

Donut::Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling) : Product{name, price, cost}, _frosting{frosting}, _sprinkles{sprinkles}, _filling{filling} { }

Donut::Donut(std::istream& ist)
{
    int temp;
    std::string a;
    std::getline(ist, _name);
    std::getline(ist, a);
    _price = std::stod(a);
    std::getline(ist, a);
    _cost = std::stod(a);
    ist>>temp;
    ist.ignore();
    _frosting = (Frosting)temp;
    ist>>temp;
    ist.ignore();
    _filling = (Filling)temp;
}

std::string Donut::to_string() 
{
    std::string result = Product::to_string();
    std::string separate = " (";
    std::string end = "";
    
    if (_frosting != Unfrosted) 
    {
        result += separate + "frosted with " + frosting_string[_frosting];
        if (_sprinkles) result += " and sprinkles";
        separate = ", ";
        end = ")";
    }
    
    if (_filling != Unfilled) 
    {
        result += separate + "filled with " + filling_string[_filling];
        end = ")";
    }
    result += end;
    return result;
}

std::string Donut::to_string_file() 
{
    std::ostringstream oss;
    oss<<std::to_string(1)<<std::endl;
    oss<<Product::to_string_file()<<std::endl;
    oss<<(int)_frosting<<std::endl;
    oss<<(int)_filling<<std::endl;
    return oss.str();
}
