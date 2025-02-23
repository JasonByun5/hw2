#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include "util.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Book : public Product {
public:
  Book(const std::string category, const std::string name, double price, 
    int qty, const std::string isbn, const std::string author);

  virtual ~Book();
  std::set<std::string> keywords() const override;
  std::string displayString() const override;
  void dump(std::ostream& os) const override;

private:
  std::string isbn_;
  std::string author_;
};

#endif

