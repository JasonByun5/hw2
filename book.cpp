#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, 
    int qty, const std::string isbn, const std::string author) : 
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{

}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const{
  set<std::string> result;
  
  //uses the parseStringToWords to put it into a set then uses an interator to add them the resutl set
  set<std::string> temp = parseStringToWords(name_);
  for (set<string>::const_iterator it = temp.begin( );it != temp.end( ); ++it)
    result.insert(*it);

  //because of the dashes it can't parese through isbn. Also no need
  
  result.insert(isbn_);
  
  set<std::string> temp2 = parseStringToWords(author_);
  for (set<string>::const_iterator it = temp2.begin( );it != temp2.end( ); ++it)
    result.insert(*it);

  return result;
}

std::string Book::displayString() const{
  string result = name_ + "\n" + 
                  "Author: " + author_ + " ISBN: " +  isbn_ + "\n" +  
                  to_string(price_) + " " + to_string(qty_) + " left.";

  return result;
}

void Book::dump(std::ostream& os) const{
  os << category_ << "\n"
    << name_ << "\n"
    << price_ << "\n"
    << qty_ << "\n"
    << isbn_ << "\n"
    << author_ << "\n";

}