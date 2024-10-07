#include "customer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

Customer::Customer() {
  ID = "0000";
  this->fName = "Default";
  this->lName = "Default";
}
Customer::~Customer() {}

Customer::Customer(string ID, string firstName, string lastName) {
  this->ID = ID;
  this->fName = firstName;
  this->lName = lastName;
}

void Customer::outputHistory() {
  cout << "ID: " << ID << "\n";
  cout << lName << ", ";
  cout << fName;
  cout << "\n";
  for (int i = history.size(); i > 0; i--) {
    cout << history[i] << endl;
  }
}

void Customer::addHistory(Movie *m, string a) {
  string s;
  s += a + ": ";
  if (m->getType() == "C") {
    s += to_string(m->getStock()) + ": ";
    s += m->getTitle() + ", ";
    s += to_string(m->getRelease()) + " " + m->getType() + "\n";
  } else if (m->getType() == "D") {
    s += to_string(m->getStock()) + ": ";
    s += m->getDirector() + ", ";
    s += m->getTitle() + " " + m->getType() + "\n";
  } else if (m->getType() == "F") {
    s += to_string(m->getStock()) + ": ";
    s += to_string(m->getReleaseMonth()) + " ";
    s += to_string(m->getRelease()) + ", ";
    s += m->getMainActor() + " " + m->getType() + "\n";
  }
  history.push_back(s);
}