
#include "store.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

void testStore1() {
  cout << "Start testStore1" << endl;
  // Should do something more, but lets just read files
  // since each implementation will
  string cfile = "testcommands-1.txt";
  stringstream out;
  ifstream fs(cfile);
  assert(fs.is_open());
  char commandType;
  string discard;
  while (fs >> commandType) {
    out << commandType;
    getline(fs, discard);
  }
  fs.close();
  string result = "IHHBRIBBIH";
  assert(out.str() == result);
  cout << "End testStore1" << endl;
}

void testStore2() {
  cout << "Start testStore2" << endl;
  ifstream customerFile("data4customers.txt");
  ifstream moviesFile("data4movies.txt");
  ifstream transactionsFile("data4commands.txt");

  if (!customerFile)
    cout << "Customer file cannot be opened" << endl;
  if (!moviesFile)
    cout << "Movie file cannot be opened" << endl;
  if (!transactionsFile)
    cout << "Transaction file cannot be opened" << endl;

  Store *S1 = new Store();
  S1->fillCustomerData(customerFile);
  S1->fillMovieData(moviesFile);
  S1->executeCommands(transactionsFile);

  cout << "End testStore2" << endl;
}

void testStoreFinal() {
  cout << "=====================================" << endl;
  cout << "Start testStoreFinal" << endl;
  cout << "Start testStore2" << endl;
  ifstream customerFile("data4customers.txt");
  ifstream moviesFile("data4movies.txt");
  ifstream transactionsFile("data4commands.txt");

  if (!customerFile)
    cout << "Customer file cannot be opened" << endl;
  if (!moviesFile)
    cout << "Movie file cannot be opened" << endl;
  if (!transactionsFile)
    cout << "Transaction file cannot be opened" << endl;

  Store *S1 = new Store();
  S1->fillCustomerData(customerFile);
  S1->fillMovieData(moviesFile);
  S1->executeCommands(transactionsFile);

  cout << "End testStore2" << endl;
  cout << "End testStoreFinal" << endl;
  cout << "=====================================" << endl;
}

void testAll() {
  testStore1();
  testStore2();
  testStoreFinal();
}
