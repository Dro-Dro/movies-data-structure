#include "comedy.h"
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

Comedy::Comedy() {
  this->stock = 0;
  this->release = 0;
  this->type = "F";
  this->title = title;
  this->director = "NA";
}

Comedy::Comedy(int stock, string title, string director, int releaseYear) {
  this->setStock(stock);
  this->setRelease(releaseYear);
  this->setTitle(title);
  this->setDirector(director);
}

Comedy::~Comedy() {}

bool Comedy::operator<(Comedy &a) const {
  Comedy temp = static_cast<Comedy &>(a);
  if (title <= temp.title) {
    if (release <= temp.release)
      return true;
    return false;
  }
  return false;
}

bool Comedy::operator>(Comedy &a) const {
  Comedy temp = static_cast<Comedy &>(a);
  if (title >= temp.title) {
    if (release >= temp.release)
      return true;
    return false;
  }
  return false;
}

bool Comedy::operator==(Comedy &a) const {
  Comedy temp = static_cast<Comedy &>(a);
  if (title == temp.title) {
    if (release == temp.release)
      return true;
    return false;
  }
  return false;
}

string Comedy::getType() { return this->type; }