#include "movie.h"
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

Movie::Movie() {
  this->stock = 0;
  this->release = 0;
  this->type = "Unknown";
  this->title = "Unknown";
  this->director = "Unknown";
}

Movie::Movie(int stock, int release, string type, string title,
             string director) {
  this->setStock(stock);
  this->setRelease(release);
  this->setType(type);
  this->setTitle(title);
  this->setDirector(director);
}

Movie::Movie(int stock, int release, string type, string title, string director,
             int releaseMonth, string mainActor) {
  this->setStock(stock);
  this->setRelease(release);
  this->setType(type);
  this->setTitle(title);
  this->setDirector(director);
  this->setReleaseMonth(releaseMonth);
  this->setMainActor(mainActor);
}

Movie::~Movie() {}

string Movie::getType() { return type; }

int Movie::getStock() { return stock; }

int Movie::getRelease() { return release; }

string Movie::getTitle() { return title; }

string Movie::getDirector() { return director; }

int Movie::getReleaseMonth() { return releaseMonth; }

string Movie::getMainActor() { return mainActor; }

void Movie::setType(const string a) { type = a; }

bool Movie::setStock(const int a) {
  if (a > -1) {
    stock = a;
    return true;
  } else {
    return false;
  }
}

bool Movie::addStock() { return setStock(getStock() - 1); }

bool Movie::reduceStock() { return setStock(getStock() - 1); }

void Movie::setRelease(const int a) { release = a; }

void Movie::setTitle(const string a) { title = a; }

void Movie::setDirector(const string a) { director = a; }

void Movie::setReleaseMonth(const int a) { releaseMonth = a; }

void Movie::setMainActor(const string a) { mainActor = a; }

bool Movie::operator<(Movie &a) const { return false; }

bool Movie::operator>(Movie &a) const { return false; }

bool Movie::operator==(Movie &a) const { return false; }