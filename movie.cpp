#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, 
    int qty, const std::string genre, const std::string rating) : 
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const{
  set<std::string> result;
  
  set<std::string> temp = parseStringToWords(name_);
  for (set<string>::const_iterator it = temp.begin( );it != temp.end( ); ++it)
    result.insert(*it);

  result.insert(genre_);
  
  return result;
}

std::string Movie::displayString() const{
  string result = name_ + "\n" + 
                  "Genre: " + genre_ + " Rating: " +  rating_ + "\n" +  
                  to_string(price_) + " " + to_string(qty_) + " left.";

  return result;
}

void Movie::dump(std::ostream& os) const{
  os << category_ << "\n"
    << name_ << "\n"
    << price_ << "\n"
    << qty_ << "\n"
    << genre_ << "\n"
    << rating_ << "\n";

}