#include "store.h"
#include "customer.h"
#include <fstream>
#include <iostream>
#include <sstream>

Store::Store() {}

void Store::fillCustomerData(ifstream &customerFile) {
  char nextLine[100]; // Size doesn't matter much, just needs to be big enough

  stringstream stream;

  string ID;
  string firstName;
  string lastName;

  while (!customerFile.eof()) {
    // Get the next line, up to 100 chars, put in nextLine
    customerFile.getline(nextLine, 100);
    stream << nextLine;
    stream >> ID;
    stream >> lastName;
    stream >> firstName;
    customers.insertItem(ID, new Customer(ID, firstName, lastName));
    stream.clear();
  }
}

void Store::fillMovieData(ifstream &movieFile) {
  string token;

  std::stringstream stream;

  char code;
  string stock;
  string director;
  // string directorLastName;
  string title;

  // Everything but Classic year is next
  string year;

  // Only for classic
  string majorActorFirstName;
  string majorActorLastName;
  string month;

  while (!movieFile.eof()) {
    char nextLine[200]; // Size doesn't matter much, just needs to be big enough

    // Get the next line, up to 999 chars, put in nextLine
    movieFile.getline(nextLine, 200);
    /* if (movieFile.eof()) {
      break;
    } */
    stream.str(nextLine);

    // string next(nextLine);
    // next.erase(remove(next.begin(), next.end(), ','), next.end());
    std::getline(stream, token, ',');
    token = removeSpaces(token);
    code = token[0];
    std::getline(stream, token, ',');
    token = removeSpaces(token);
    stock = token;

    std::getline(stream, token, ',');
    token = removeSpaces(token);
    director = token;

    std::getline(stream, token, ',');
    token = removeSpaces(token);
    title = token;

    if (code == 'C') {
      stream >> majorActorFirstName;
      stream >> majorActorLastName;
      stream >> month;
      stream >> year;

      Classic *cl = new Classic(stoi(stock), title, director,
                                majorActorFirstName + " " + majorActorLastName,
                                stoi(year), stoi(month));
      classics.push_back(cl);

    } else if (code == 'F') {
      stream >> year;
      Comedy *cm = new Comedy(stoi(stock), title, director, stoi(year));
      comedies.push_back(cm);

    } else if (code == 'D') {
      stream >> year;
      Drama *dr = new Drama(stoi(stock), title, director, stoi(year));
      dramas.push_back(dr);

    } else {
      std::cout << "Invalid movie code in movie file\n\n";
    }
    stream.clear();
  }
}

string Store::removeSpaces(string input) {
  string output;
  bool isStart = true;
  for (int i = 0; i < input.length(); i++) {
    if (!(isStart && input[i] == ' ')) {
      isStart = false;
      output += input[i];
    }
  }
  return output;
}

void Store::executeCommands(ifstream &commandFile) {
  while (!commandFile.eof()) {
    string commandLine;
    getline(commandFile, commandLine);
    if (commandFile.eof()) {
      break;
    }
    processCommand(commandLine);
  }
}

void Store::processCommand(const string &commandLine) {
  stringstream stream(commandLine);
  char commandCode;
  stream >> commandCode;
  switch (commandCode) {
  case 'I':
    // outputInventory();
    break;
  case 'H': {
    string ID;
    stream >> ID;
    outputCustomerHistory(ID);
    break;
  }
  case 'B': {
    string ID;
    stream >> ID;
    char media;
    stream >> media;
    if (media != 'D') {
      cout << "Invalid media type" << endl << endl;
      break;
    }
    processBorrowCommand(stream, ID);
    break;
  }
  case 'R': {
    string ID;
    stream >> ID;
    char media;
    stream >> media;
    if (media != 'D') {
      cout << "Invalid media type" << endl << endl;
      break;
    }
    processReturnCommand(stream, ID);
    break;
  }
  default:
    cout << "Invalid command code" << endl << endl;
  }
}

void Store::outputInventory() {
  sortF();
  sortD();
  sortC();

  for (Comedy *c : comedies) {
    std::cout << c->getStock() << ": ";
    std::cout << c->getTitle() << ", ";
    std::cout << c->getRelease() << " " << c->getType() << "\n";
    // cout << *c;
  }
  for (Drama *d : dramas) {
    std::cout << d->getStock() << ": ";
    std::cout << d->getDirector() << ", ";
    std::cout << d->getTitle() << " " << d->getType() << "\n";
    // cout << *d;
  }
  for (Classic *c : classics) {
    std::cout << c->getStock() << ": ";
    std::cout << c->getReleaseMonth() << " ";
    std::cout << c->getRelease() << ", ";
    std::cout << c->getMainActor() << " " << c->getType() << "\n";
  }
  std::cout << "\n";
}

// sorts comedy movies
void Store::sortF() {
  for (int i = 0; i < comedies.size(); i++) {
    if (comedies[i + 1] < comedies[i]) {
      Comedy *cm = new Comedy(
          comedies[i + 1]->getStock(), comedies[i + 1]->getTitle(),
          comedies[i + 1]->getDirector(), comedies[i + 1]->getRelease());
      comedies[i + 1] = comedies[i];
      comedies[i] = cm;
    } else if (comedies[i + 1] > comedies[i]) {
      Comedy *cm = new Comedy(
          comedies[i + 1]->getStock(), comedies[i + 1]->getTitle(),
          comedies[i + 1]->getDirector(), comedies[i + 1]->getRelease());
      comedies[i + 1] = comedies[i];
      comedies[i] = cm;
    }
  }
}

// sorts drama movies
void Store::sortD() {
  for (int i = 0; i < dramas.size(); i++) {
    if (dramas[i + 1] < dramas[i]) {
      Drama *cm =
          new Drama(dramas[i + 1]->getStock(), dramas[i + 1]->getTitle(),
                    dramas[i + 1]->getDirector(), dramas[i + 1]->getRelease());
      dramas[i + 1] = dramas[i];
      dramas[i] = cm;
    } else if (dramas[i + 1] > dramas[i]) {
      Drama *cm =
          new Drama(dramas[i + 1]->getStock(), dramas[i + 1]->getTitle(),
                    dramas[i + 1]->getDirector(), dramas[i + 1]->getRelease());
      dramas[i + 1] = dramas[i];
      dramas[i] = cm;
    }
  }
}

// sorts classic movies
void Store::sortC() {
  for (int i = 0; i < classics.size(); i++) {
    if (classics[i + 1] < classics[i]) {
      Classic *cm = new Classic(
          classics[i + 1]->getStock(), classics[i + 1]->getTitle(),
          classics[i + 1]->getDirector(), classics[i + 1]->getMainActor(),
          classics[i + 1]->getRelease(), classics[i + 1]->getReleaseMonth());
      classics[i + 1] = classics[i];
      classics[i] = cm;
    } else if (classics[i + 1] > classics[i]) {
      Classic *cm = new Classic(
          classics[i + 1]->getStock(), classics[i + 1]->getTitle(),
          classics[i + 1]->getDirector(), classics[i + 1]->getMainActor(),
          classics[i + 1]->getRelease(), classics[i + 1]->getReleaseMonth());
      classics[i + 1] = classics[i];
      classics[i] = cm;
    }
  }
}

void Store::outputCustomerHistory(const string &customerID) {
  Customer *customer = customers.retrieve(customerID);
  if (customer == nullptr) {
    cout << "No customer with ID " << customerID << endl << endl;
  } else {
    customer->outputHistory();
  }
}

void Store::processBorrowCommand(stringstream &stream, string ID) {
  char code;
  stream >> code;
  if (code == 'D') {
    string director, title;
    getline(stream, director, ',');
    director = removeSpaces(director);
    getline(stream, title, ',');
    title = removeSpaces(title);
    Drama *movie = findDramaMovie(director, title);
    if (movie != nullptr) {
      Customer *customer = customers.retrieve(ID);
      if (customer != nullptr) {
        borrowMovie(customer, movie);
      } else {
        cout << "No customer with ID " << stream.str() << endl << endl;
      }
    } else {
      cout << "No movie with title " << title << endl << endl;
    }
  } else if (code == 'C') {
    string month, year, majorActorFirstName, majorActorLastName;
    stream >> month >> year >> majorActorFirstName >> majorActorLastName;
    Classic *movie =
        findClassicMovie(stoi(month), stoi(year),
                         majorActorFirstName + " " + majorActorLastName);
    if (movie != nullptr) {
      Customer *customer = customers.retrieve(ID);
      if (customer != nullptr) {
        borrowMovie(customer, movie);
      } else {
        cout << "No customer with ID " << stream.str() << endl << endl;
      }
    } else {
      cout << "No movie with title " << stream.str() << endl << endl;
    }
  } else if (code == 'F') {
    string title, year;
    getline(stream, title, ',');
    title = removeSpaces(title);
    stream >> year;
    Comedy *movie = findComedyMovie(title, stoi(year));
    if (movie != nullptr) {
      Customer *customer = customers.retrieve(ID);
      if (customer != nullptr) {
        borrowMovie(customer, movie);
      } else {
        cout << "No customer with ID " << stream.str() << endl << endl;
      }
    } else {
      cout << "No movie with title " << title << endl << endl;
    }
  } else {
    cout << "Invalid movie code in command file" << endl << endl;
  }
}

void Store::processReturnCommand(stringstream &stream, string ID) {
  char code;
  stream >> code;
  if (code == 'D') {
    string director, title;
    getline(stream, director, ',');
    director = removeSpaces(director);
    getline(stream, title, ',');
    title = removeSpaces(title);
    Drama *movie = findDramaMovie(director, title);
    if (movie != nullptr) {
      Customer *customer = customers.retrieve(ID);
      if (customer != nullptr) {
        returnMovie(customer, movie);
      } else {
        cout << "No customer with ID " << stream.str() << endl << endl;
      }
    } else {
      cout << "No movie with title " << title << endl << endl;
    }
  } else if (code == 'C') {
    string month, year, majorActorFirstName, majorActorLastName;
    stream >> month >> year >> majorActorFirstName >> majorActorLastName;
    Classic *movie =
        findClassicMovie(stoi(month), stoi(year),
                         majorActorFirstName + " " + majorActorLastName);
    if (movie != nullptr) {
      Customer *customer = customers.retrieve(ID);
      if (customer != nullptr) {
        returnMovie(customer, movie);
      } else {
        cout << "No customer with ID " << stream.str() << endl << endl;
      }
    } else {
      cout << "No movie with title " << stream.str() << endl << endl;
    }
  } else if (code == 'F') {
    string title, year;
    getline(stream, title, ',');
    title = removeSpaces(title);
    stream >> year;
    Comedy *movie = findComedyMovie(title, stoi(year));
    if (movie != nullptr) {
      Customer *customer = customers.retrieve(ID);
      if (customer != nullptr) {
        returnMovie(customer, movie);
      } else {
        cout << "No customer with ID " << stream.str() << endl << endl;
      }
    } else {
      cout << "No movie with title " << title << endl << endl;
    }
  } else {
    cout << "Invalid movie code in command file" << endl << endl;
  }
}

Drama *Store::findDramaMovie(const string &director, const string &title) {
  for (Drama *movie : dramas) {
    if (movie->getDirector() == director && movie->getTitle() == title) {
      return movie;
    }
  }
  return nullptr;
}

Classic *Store::findClassicMovie(int month, int year, const string &actor) {
  for (Classic *movie : classics) {
    if (movie->getReleaseMonth() == month && movie->getRelease() == year &&
        movie->getMainActor() == actor) {
      return movie;
    }
  }
  return nullptr;
}

Comedy *Store::findComedyMovie(const string &title, int year) {
  for (Comedy *movie : comedies) {
    if (movie->getTitle() == title && movie->getRelease() == year) {
      return movie;
    }
  }
  return nullptr;
}

void Store::borrowMovie(Customer *customer, Movie *movie) {
  if (movie->reduceStock()) {
    customer->addHistory(movie, "borrow");
  } else {
    cout << "Movie not in stock" << endl << endl;
  }
}

void Store::returnMovie(Customer *customer, Movie *movie) {
  movie->addStock();
  customer->addHistory(movie, "return");
}

void Store::Inventory() {
  for (int i = 0; i < classics.size(); i++) {
  }
}
