#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, 
    int qty, const std::string size, const std::string brand) : 
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const{
  set<std::string> result;
  
  set<std::string> temp = parseStringToWords(name_);
  for (set<string>::const_iterator it = temp.begin( );it != temp.end( ); ++it)
    result.insert(*it);

  set<std::string> temp2 = parseStringToWords(brand_);
  for (set<string>::const_iterator it = temp2.begin( );it != temp2.end( ); ++it)
    result.insert(*it);
  
  return result;
}

std::string Clothing::displayString() const{
  string result = name_ + "\n" + 
                  "Size: " + size_ + " Brand: " +  brand_ + "\n" +  
                  to_string(price_) + " " + to_string(qty_) + " left.";

  return result;
}

void Clothing::dump(std::ostream& os) const{
  os << category_ << "\n"
     << name_ << "\n"
     << price_ << "\n"
     << qty_ << "\n"
     << size_ << "\n"
     << brand_ << "\n";

}