#include <sstream>
#include <iomanip>
#include "mydatastore.h"
#include "util.h"
#include <vector>


MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
  for (Product* p : products_) {
    delete p;
  }
  for (User* u : users_) {
    delete u;
  }
}

void MyDataStore::addProduct(Product* p){
  // adds the product to the product vector for storage
  products_.push_back(p);

  //makes a set based on the keywords
  std::set<std::string> productKeywords = p->keywords();

  //converts the letters to lower case for easier future user
  //matches the keyword to the product and stores it on the map
  for(std::string keyword : productKeywords){
    keyword = convToLower(keyword);
    keywordMap_[keyword].insert(p);
  }
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
}

std::vector<Product*> MyDataStore::search(
  std::vector<std::string>& terms, int type){
  
  std::set<Product*> result;

  //will use later because for SET Union you need something to compare to
  bool firstKeyword = false;

  if(terms.empty()){
    return {};
  }
  

  for(std::string term : terms){
    //converts the term to compare to the keywords in the map
    std::string keyword = convToLower(term);
    
    if(keywordMap_.find(keyword) == keywordMap_.end()){
      if(type == 0){
        return {};
      }
      continue;
    }

    std::set<Product*> temp = keywordMap_[keyword];
    

    if(!firstKeyword){
      result = temp;
      firstKeyword = true;
    } else{
      if(type == 0){
        result = setIntersection(result, temp);
      }else{
        result = setUnion(result,temp);
      }
    }
  }

  return std::vector<Product*>(result.begin(), result.end());
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << std::endl;

  for(Product* p : products_){
    p->dump(ofile);
  }

  ofile << "</products>" << std::endl;

  ofile << "<users>" << std::endl;

  for(User* u : users_){
    u->dump(ofile);
  }

  ofile << "</users>" << std::endl;
}


void MyDataStore::addToCart(const std::string& username, Product* p){
  std::string lowerUsername = convToLower(username);
  
  //checks to see if the user exists
  bool userExists = false;
  for (User* user : users_) {
    if (convToLower(user->getName()) == lowerUsername) {
      userExists = true;
      break;
    }
  }

  if (!userExists) {
    std::cout << "Invalid request" << std::endl<< std::flush;
    return;
  }

  if(p == nullptr){
    std:: cout << "Invalid request" << std::endl << std::flush;
    return;
  }
  
  carts_[lowerUsername].push_back(p);

}

void MyDataStore::viewCart(const std::string& username){
  std::string lowerUsername = convToLower(username);
  
  if(carts_.find(lowerUsername) == carts_.end()){
    std::cout << "Invalid username" << std::endl;
    return;
  }

  std::vector<Product*>& cart = carts_[lowerUsername];
  if(cart.empty()){
    std::cout << "Cart is empty" << std::endl;
    return;
  }

  int index = 1;
  for(Product* p : cart){
    std::cout << "Item " << index++ << ": " << std::endl;
    std::cout << p->displayString() << std::endl;
  }
}

void MyDataStore::buyCart(const std::string& username){
  std::string lowerUsername = convToLower(username);

  User* userPtr = nullptr;
  for (User* user : users_) {
    if(convToLower(user->getName()) == lowerUsername){
      userPtr = user;
      break;
    }
  }

  if(!userPtr){
    std::cout << "Invalid username" << std::endl;
    return;
  }

  std::vector<Product*>& cart = carts_[lowerUsername];
  std::vector<Product*> newCart;

  for(size_t i = 0; i < cart.size(); i++) {
    Product* product = cart[i];

    if(product->getQty() > 0 && userPtr->getBalance() >= product->getPrice()) {
      product->subtractQty(1);
      userPtr->deductAmount(product->getPrice());
    }else{
      newCart.push_back(product);
    }
  }

  carts_[lowerUsername] = newCart;
}