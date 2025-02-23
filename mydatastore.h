#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <set>
#include <vector>
#include <string>
#include <map>

class MyDataStore : public DataStore{
public:
  MyDataStore();
  ~MyDataStore();

  //taken from MyDataStore
  void addProduct(Product* p) override;
  void addUser(User* u) override;
  std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
  void dump(std::ostream& ofile) override;


  //prototyped from amazon.cpp
  void addToCart(const std::string& username, Product* p);
  void viewCart(const std::string& username);
  void buyCart(const std::string& username);

private:
  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::map<std::string, std::set<Product*>> keywordMap_;

  std::map<std::string, std::vector<Product*>> carts_;
};

#endif

