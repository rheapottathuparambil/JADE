#include "java.h"

Java::Java(std::string name, double price, double cost, Darkness darkness) : Product{name, price, cost}, _darkness{darkness} { }

Java::Java(std::istream& ist)
{
    int temp,t;
    std::string a;
    std::getline(ist, _name);
    std::getline(ist, a);
    _price = std::stod(a);
    std::getline(ist, a);
    _cost = std::stod(a);
    ist>>temp;
    ist.ignore();
    _darkness = (Darkness)temp;
    ist>>temp;
    int i;
    for(i=0;i<temp;i++)
    {
        ist>>t;
        ist.ignore();
        Shot a = (Shot)t;
        _shots.push_back(a);
    }
}

void Java::add_shot(Shot shot) 
{
    _shots.push_back(shot);
}

std::string Java::to_string() 
{
    std::string result =  Product::to_string() + " (" + darkness_to_string[_darkness] + ")";
    std::string separate = " with ";
    for (auto s : _shots) 
    {
        result += separate + shot_to_string[s]; 
        separate = ", ";
    }
    return result;
}

std::string Java::to_string_file() 
{
    int size = _shots.size();
    std::ostringstream oss;
    oss<<std::to_string(0)<<std::endl;
    oss<<Product::to_string_file()<<std::endl;
    oss<<(int)_darkness<<std::endl;
    oss<<size<<std::endl;
    for (int i=0;i<size;i++) 
    {
        oss<<(int)_shots[i]<<std::endl;
    }
    return oss.str();
}
