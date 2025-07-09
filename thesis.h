#ifndef THESIS_H
#define THESIS_H

// Thesis Class
// The thesis class is the derived class from the literature classes. 
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

class thesis: public literature
{
private:
  string supervisor;
  string university;
public:
// Default Constructor 
  thesis(){};
// Parameterised Constructor
  thesis(string Title, std::shared_ptr<std::vector<string>> Author, string Supervisor, string University):
    literature{Title, Author, "Thesis"}, supervisor(Supervisor), university(University)
  {}
// Destructor
  ~thesis(){};
// Copy constructor
  thesis(const thesis& old);

// Move constructor
  thesis(thesis&& old);

// Copy assignment operator
  thesis& operator=(const thesis& old);

// Move assignment operator
  thesis& operator=(thesis&& old);

// Functions
// Setters and getters for Thesis class variables
  string get_supervisor(){return supervisor;}
  string get_university(){return university;}
  void set_supervisor(string new_supervisor){supervisor = new_supervisor;}
  void set_university(string new_university){university = new_university;}

// Other functions for Thesis class. Defined in cpp file.
  void print_information();
  void edit_information();
  std::string get_type(){return "thesis";}
  string data_output();

};
#endif