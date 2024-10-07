#include <iostream>
#include <fstream>
#include <vector>
#include "inventory.h"
#include "command.h"
using namespace std;

// destructor
Inventory::~Inventory() {
    for (auto &j : comedies) {
        delete j;
    }
    for (auto &j : dramas) {
        delete j;
    }
    for (auto &j : classics) {
        delete j;
    }
}

// inventory print command
// true if it can print, false if not
bool Inventory::printInventory() {
    if (classics.size() == 0 && comedies.size() == 0 && dramas.size() == 0) {return false;}
    else {
        for (auto &j : comedies) {
            cout << "F " << j.title << " " << j.releaseYear << " " << j.borrowedNum << " " << j.stock << endl;
        }
        for (auto &j : dramas) {
            cout << "D " << j.director << " " << j.title << " " << j.borrowedNum << " " << j.stock << endl;
        }
        for (auto &j : classics) {
            cout << "C " << j.releaseMonth << " " << j.releaseYear << " " << j.majorActor << " " << j.borrowedNum << " " << j.stock << endl;
        }
        return true;
    }
}

// hash function for index
int Inventory::hashFunc(char c) {
    return (c - 'a');
}

// checks to see if the movie exists already
bool Inventory::ifExist(Movie* s) {
    for (auto &j : comedies) {
        if (j == s) {
            return true;
        }
    }
    for (auto &j : dramas) {
        if (j == s) {
            return true;
        }
    }
    for (auto &j : classics) {
        if (j == s) {
            return true;
        }
    }
    return false;
}

// adding a movie to the inventory
bool Inventory::addMovie(char c, Movie* m) {
    if (!ifExist(m)) {
        if (c == 'F') {
            comedies.push_back(m);
            return true;
        }
        if (c == 'C') {
            classics.push_back(m);
            return true;
        }
        if (c == 'D') {
            dramas.push_back(m);
            return true;
        }
    }
    return false;
}

// reads file and takes movies
void Inventory::movieFileReader(const string &filename) {
    // Read from the text file
    ifstream iFile(filename);
    if (!iFile.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
    } else {
         // string representation of the text line by line
        string line;

        // reads the textfile line by line
        while (getline(iFile, line)) {
            if (line[0] == 'F') {
                movieReadHelper(line);
            } else if (line[0] == 'D') {
                movieReadHelper(line);
            } else if (line[0] == 'C') {
                movieReadHelper(line);
            } else {
                cout << "ERROR! Movie Code: [" << line[0] << "] is invalid!" << endl;
            }
            line.erase();
        }
    }
    
    // Close the file
    iFile.close();
}

// helps input the movies into the database aka hash table
// returns true if the movie can be put in, false if not
bool Inventory::movieReadHelper(string& s) {
    vector<string> z;
    int lineCheck;
    if (s[0] == 'F' || s[0] == 'D') {
        // movie type
        string t(1, s[0]);
        z.push_back(t);
        lineCheck = s.find_first_of(",");
        s.erase (0, lineCheck);
        // stock s[1]
        lineCheck = s.find_first_of(",");
        z.push_back(s.substr(0, lineCheck));
        s.erase(0, lineCheck);
        // director name s[2]
        lineCheck = s.find_first_of(",");
        z.push_back(s.substr(0, lineCheck));
        s.erase(0, lineCheck);
        // movie title s[3]
        lineCheck = s.find_first_of(",");
        z.push_back(s.substr(0, lineCheck));
        s.erase(0, lineCheck);
        // release year s[4]
        z.push_back(s);

        if (z[0] == "F") {
            comedyMovieIsExist(s[3], s[4]);
        } else if (z[0] == "D") {
            dramaMovieIsExist(s[2], s[3]);
        }
    } else if (s[0] == 'C') {
        // movie type s[0]
        string t(1, s[0]);
        z.push_back(t);
        lineCheck = s.find_first_of(",");
        s.erase(0, lineCheck);
        // stock s[1]
        lineCheck = s.find_first_of(",");
        z.push_back(s.substr(0, lineCheck));
        s.erase(0, lineCheck);
        // director s[2]
        lineCheck = s.find_first_of(",");
        z.push_back(s.substr(0, lineCheck));
        s.erase(0, lineCheck);
        // title s[3]
        lineCheck = s.find_first_of(",");
        z.push_back(s.substr(0, lineCheck));
        s.erase(0, lineCheck);
        // major actor first name s[4]
        lineCheck = s.find_first_of(" ");
        z.push_back(s.substr(0, lineCheck));
        s.erase(0, lineCheck);
        // major actor last name s[5]
        lineCheck = s.find_first_of(" ");
        z.push_back(s.substr(0, lineCheck));
        s.erase(0, lineCheck);
        // release month s[6]
        lineCheck = s.find_first_of(" ");
        z.push_back(s.substr(0, lineCheck));
        s.erase(0, lineCheck);
        // release year s[7]
        z.push_back(s);

        string p = s[4] + " " + s[5];
        classicMovieIsExist(s[6], s[7], p);
    }
}

// reads customer file and puts them into the database
void Inventory::customerFileReader(const string &filename) {
    // Read from the text file
    ifstream iFile(filename);
    if (!iFile.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
    } else {
         // string representation of the text line by line
        string line;

        // reads the textfile line by line
        while (getline(iFile, line)) {
            int customerID;
            string customerLastName;
            string customerFirstName;
            int space = 0;
            space = line.find_first_of(" ");
            customerID = stoi(line.substr(0, space));
            line.erase(0, space);

            space = line.find_first_of(" ");
            customerLastName = line.substr(0, space);
            line.erase(0, space);

            customerFirstName = line;
            if (!customerIsExist(customerID)) {
                Customer tmp = new Customer(customerFirstName, customerLastName, customerID);
                customerList[customerID] = tmpCust;
            }
            line.erase();
        }
    }
    
    // Close the file
    iFile.close();
}

// checks if a customer exists
bool Inventory::customerIsExist(const int c) {
    return customerList.count(c) == 1;
}