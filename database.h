#ifndef DATABASE_H
#define DATABASE_H

// Database Class
// A database class is used to manage the literatures more easily. Individual data are accessed through the database.
// It is constructed as a vector pair of literature entries and a corresponding index, so actions can be done to them.
// It is a class outside of the literature inheritance chain.
// Author: Hojae Lim

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<sstream>
#include<algorithm>
#include "literature.h"

using std::string;

class database
{
private:
  std::vector<std::pair<int, std::shared_ptr<literature> >> entries; // Pair vector of index and entry
  int entry_index{1}; // Used to assign index values to added entries.

public:
// Default Constructor 
  database(){}

// Parameterised Constructor
// Takes entries, identifies maximum index within entries then add 1 to entry index so that subsequent additions will have correct index number.
  database(const std::vector<std::pair<int, std::shared_ptr<literature> >>& entryVector):
    entries{entryVector}
  {
    if(!entries.empty())
    {
      auto max_entry_index = std::max_element(entries.begin(), entries.end(), [](const auto& left, const auto& right)
      {
        return left.first < right.first;
      });
      entry_index = max_entry_index->first + 1;
    }
  }

// Destructor
  ~database(){}

// Copy constructor
  database(const database& old);

// Move constructor
  database(database&& old);

// Copy assignment operator
  database& operator=(const database& old);

// Move assignment operator
  database& operator=(database&& old);

  void add_entry(std::shared_ptr<literature> new_literature); // Used to add entries automatically, by other functions
  void add_manual_entry(); // Used to add entries manually, by user
  void add_search_entry(std::pair<int, std::shared_ptr<literature>> searched_entry); // Used with search functions, to add to a new database searched values with stored index numbers. 
  void delete_entry();
  void edit_entry();
  database search_title(string title_input);
  database search_author(string author_input);
  database search_type(string type_input);
  void average_book_price();
  void print_information(); // Function that uses print function from literature classes to print all informations of the database.
  void write_data(); // Used to write data to a new file of all entries in the database.
};


#endif