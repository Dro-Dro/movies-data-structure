#include "classic.h"
#include "movie.h"
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

Classic::Classic() {
  this->stock = 0;
  this->release = 0;
  this->type = "C";
  this->title = title;
  this->director = "NA";
  this->releaseMonth = 0;
  this->mainActor = "NA";
}

Classic::Classic(int stock, string title, string director, string mainActor,
                 int releaseYear, int monthReleased) {
  this->setStock(stock);
  this->setRelease(releaseYear);
  this->setTitle(title);
  this->setDirector(director);
  this->setReleaseMonth(monthReleased);
  this->setMainActor(mainActor);
}

Classic::~Classic() {}

bool Classic::operator<(Classic &a) const {
  Classic temp = a;
  if ((releaseMonth + release) <= (temp.releaseMonth + temp.release)) {
    if (mainActor <= temp.mainActor)
      return true;
    return false;
  }
  return false;
}

bool Classic::operator>(Classic &a) const {
  Classic temp = static_cast<Classic &>(a);
  if ((releaseMonth + release) >= (temp.releaseMonth + temp.release)) {
    if (mainActor >= temp.mainActor)
      return true;
    return false;
  }
  return false;
}

bool Classic::operator==(Classic &a) const {
  Classic temp = static_cast<Classic &>(a);
  if ((releaseMonth + release) == (temp.releaseMonth + temp.release)) {
    if (mainActor == temp.mainActor)
      return true;
    return false;
  }
  return false;
}

string Classic::getType() { return type; }