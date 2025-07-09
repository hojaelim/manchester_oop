#ifndef LITERATURE_H
#define LITERATURE_H

// Literature Class
// The literature class is the base class for the literature classes that are used. It has virtual functions that are inherited to the derived classes.
// Author: Hojae Lim

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<sstream>
#include<algorithm>

using std::string;

class literature
{
protected:
  string title;
  std::shared_ptr<std::vector<string>> author; // Author defined as shared pointer in case many objects need to access it. Also takes in multiple inputs.
  string literature_type;

public:
// Default Constructor
  literature(){};

// Parameterised Constructor
  literature(string Title, std::shared_ptr<std::vector<string>> Author, string literatureType):
    title(Title), author(Author), literature_type(literatureType)
  {}

// Destructor
  virtual ~literature(){} // Needs to be since virtual functions are used

// Copy constructor
  literature(const literature& old);

// Move constructor
  literature(literature&& old);

// Copy assignment operator
  literature& operator=(const literature& old);

// Move assignment operator
  literature& operator=(literature&& old);

// Functions
// Setters and getters
  string get_title(){return title;}
  std::shared_ptr<std::vector<string>> get_author(){return author;}
  void set_title(string new_title){title = new_title;}
  void set_author(std::shared_ptr<std::vector<string>> new_author){author = new_author;}

// Virtual functions that are accessed by derived classes.
  virtual std::string get_type() = 0;
  virtual void print_information();
  virtual void edit_information() = 0; 
  virtual string data_output() = 0;
};

#endif