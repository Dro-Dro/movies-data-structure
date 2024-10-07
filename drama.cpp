#include "drama.h"
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

Drama::Drama() {
  this->stock = 0;
  this->release = 0;
  this->type = "D";
  this->title = title;
  this->director = "NA";
}

Drama::Drama(int stock, string title, string director, int releaseYear) {
  this->setStock(stock);
  this->setRelease(releaseYear);
  this->setTitle(title);
  this->setDirector(director);
}

Drama::~Drama() {}

bool Drama::operator<(Drama &a) const {
  Drama temp = static_cast<Drama &>(a);
  if (director <= temp.director) {
    if (title <= temp.title)
      return true;
    return false;
  }
  return false;
}

bool Drama::operator>(Drama &a) const {
  Drama temp = static_cast<Drama &>(a);
  if (director >= temp.director) {
    if (title >= temp.title)
      return true;
    return false;
  }
  return false;
}

bool Drama::operator==(Drama &a) const {
  Drama temp = static_cast<Drama &>(a);
  if (director == temp.director) {
    if (title == temp.title)
      return true;
    return false;
  }
  return false;
}