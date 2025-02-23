#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  trim(rawWords);
  std::set<string> keyWords;
  std::string temp;
  
  //loops thorught the word and checks if it is a number or now. If it is then it will add, else will not
  for(size_t i =0; i< rawWords.length(); i++){
    if(std::isalnum(rawWords[i])){
      temp.push_back(std::tolower(rawWords[i]));
    }
    else{
      if(!temp.empty() && std::isdigit(temp[0]) && (i + 1 < rawWords.size()) && std::isdigit(rawWords[i+1])){
        temp.push_back(rawWords[i]);
      }else{
        if(temp.length() >= 2){
          keyWords.insert(temp);
        }
        temp.clear();
      }
    }
  }

  //checks that last few letters left if they can make up a keyword
  if(temp.length() >= 2){
    keyWords.insert(temp);
  }


  return keyWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
