#ifndef COMEDY_H
#define COMEDY_H

#include "movie.h"
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Comedy : public Movie {
public:
  Comedy();

  Comedy(int stock, std::string title, std::string director, int releaseYear);

  ~Comedy();

  string getType();

  bool operator<(Comedy &a) const;

  bool operator>(Comedy &a) const;

  bool operator==(Comedy &a) const;
};

#endif