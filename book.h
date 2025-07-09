#ifndef BOOK_H
#define BOOK_H

// Book Class
// The book class is the derived class from the literature classes. 
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

class book: public literature
{
private:
  string publisher;
  string subject;
  double price;

public:
// Default Constructor
  book(){};
// Parameterised Constructor
  book(string Title, std::shared_ptr<std::vector<string>> Author, string Publisher, string Subject, double Price):
    literature{Title, Author, "Book"}, publisher(Publisher), subject(Subject), price(Price)
  {}
// Destructor
  ~book(){};

// Copy constructor
  book(const book& old);

// Move constructor
  book(book&& old);

// Copy assignment operator
  book& operator=(const book& old);

// Move assignment operator
  book& operator=(book&& old);

// Functions
// Setters and getters for Book class variables
  string get_publisher(){return publisher;}
  string get_subject(){return subject;}
  double get_price(){return price;}
  void set_publisher(string new_publisher){publisher = new_publisher;}
  void set_subject(string new_subject){subject = new_subject;}
  void set_price(double new_price){price = new_price;}

// Other functions for Book class. Defined in cpp file.
  void print_information();
  void edit_information();
  string get_type(){return "Book";}
  string data_output();
};
#endif