#ifndef CLASSIC_H
#define CLASSIC_H

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

class Classic : public Movie {
public:
  Classic();

  Classic(int stock, string title, string director, string mainActor,
          int releaseYear, int monthReleased);

  ~Classic();
  string getType();

  bool operator<(Classic &a) const;

  bool operator>(Classic &a) const;

  bool operator==(Classic &a) const;
};

#endif