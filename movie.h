#ifndef MOVIE_H
#define MOVIE_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

class Movie {
public:
  Movie();
  Movie(int stock, int release, string type, string title, string director);
  Movie(int stock, int release, string type, string title, string director,
        int releaseMonth, string mainActor);
  ~Movie();

  int getStock();
  int getRelease();
  virtual string getType();
  string getTitle();
  string getDirector();
  virtual int getReleaseMonth();
  virtual string getMainActor();

  void setType(string a);
  bool setStock(int a);
  bool addStock();
  bool reduceStock();
  void setRelease(int a);
  void setTitle(string a);
  void setDirector(string a);

  virtual void setReleaseMonth(int a);

  virtual void setMainActor(string a);

  virtual bool operator<(Movie &a) const;

  virtual bool operator>(Movie &a) const;

  virtual bool operator==(Movie &a) const;

protected:
  string type;
  string director;
  string title;
  string mainActor;
  int stock;
  int release;
  int releaseMonth;
};

#endif