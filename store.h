#ifndef STORE_H
#define STORE_H

#include "classic.h"
#include "comedy.h"
#include "customer.h"
#include "drama.h"
#include "hashtable.cpp"
#include "hashtable.h"
#include <vector>

using namespace std;

class Store {
public:
  Store();
  string removeSpaces(string input);
  void fillCustomerData(ifstream &customerFile);
  void fillMovieData(ifstream &movieFile);
  void executeCommands(ifstream &commandFile);
  void processCommand(const string &commandLine);
  void outputInventory();
  void sortF();
  void sortD();
  void sortC();
  void outputCustomerHistory(const string &customerID);
  void processBorrowCommand(stringstream &stream, string ID);
  void processReturnCommand(stringstream &stream, string ID);
  Drama *findDramaMovie(const string &director, const string &title);
  Classic *findClassicMovie(int month, int year, const string &actor);
  Comedy *findComedyMovie(const string &title, int year);
  void borrowMovie(Customer *customer, Movie *movie);
  void Inventory();
  void returnMovie(Customer *customer, Movie *movie);

private:
  HashTable<Customer> customers;
  vector<Comedy *> comedies;
  vector<Drama *> dramas;
  vector<Classic *> classics;
};

#endif