#ifndef DRAMA_H
#define DRAMA_H

#include "movie.h"
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Drama : public Movie {
public:
  Drama();

  Drama(int stock, string title, string director, int releaseYear);

  string getDirector() { return director; }

  ~Drama();

  bool operator<(Drama &a) const;

  bool operator>(Drama &a) const;

  bool operator==(Drama &a) const;

private:
};

#endif