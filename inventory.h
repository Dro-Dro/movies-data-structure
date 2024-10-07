//Inventory Class holds all movies in a hashtable and a map of customers

#include <iostream>
#include <map>
#include <vector>

#include "movie.h"
#include "customer.h"

using namespace std;

static const int tableSize = 26;
class Inventory {
friend class Command;
public:

    // hash function for index
    int hashFunc(char c);

    // checks to see if the movie exists already
    bool ifExist(Movie*);

    // adding a movie to the inventory
    bool addMovie(char, Movie*);

    // inventory print command
    // true if it can print false it not
    bool printInventory();

    // reads file and takes movies
    void movieFileReader(const string &filename);

    // helps input the movies into the database aka hash table
    // returns true if the movie can be put in, false if not
    bool movieReadHelper(string& s);

    // reads customer file and puts them into the database
    void customerFileReader(const string &filename);

    // checks if a customer exists
    bool customerIsExist(const int c);

    // constructor
    Inventory() = default;

    // destructor
    ~Inventory();

    // copy not allowed
    Inventory(const Inventory &other) = delete;

    // move not allowed
    Inventory(Inventory &&other) = delete;

    // assignment not allowed
    Inventory &operator=(const Inventory &other) = delete;

    // move assignment not allowed
    Inventory &operator=(Inventory &&other) = delete;

private:

    // vectors storing movies under genres
    vector<Movie*> comedies;
    vector<Movie*> dramas;
    vector<Movie*> classics;

    // customer list using customerID as key
    map<int, Customer*> customerList;
};
