#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "movie.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Customer {
public:
  Customer();

  Customer(string c, string f, string l);

  ~Customer();

  // getters
  string getFName();

  string getLName();

  string getID();

  // setters
  void setFName(string);

  void setLName(string);

  void setID(int);

  void addHistory(Movie *movie, std::string type);

  void outputHistory();

private:
  string fName;
  string lName;
  string ID;
  vector<string> history;
};

#endif