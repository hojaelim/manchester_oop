#ifndef JOURNAL_H
#define JOURNAL_H

// Journal Class
// The journal class is the derived class from the literature classes. 
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


class journal: public literature
{
private:
  double impact_factor;
  int volume_number;
// Can take in multiple inputs; represent as pointer.
  std::shared_ptr<std::vector<string>> editor_names;
  std::shared_ptr<std::vector<string>> scope;
public:
// Default Constructor
  journal(){};
// Parameterised Constructor
  journal(string Title, std::shared_ptr<std::vector<string>> Author, int volumeNumber, std::shared_ptr<std::vector<string>> editorNames, std::shared_ptr<std::vector<string>> Scope, double impactFactor):
    literature{Title, Author, "Journal"}, volume_number(volumeNumber), editor_names(editorNames), scope(Scope), impact_factor(impactFactor)
  {}
// Destructor
  ~journal(){};

// Copy constructor
  journal(const journal& old);

// Move constructor
  journal(journal&& old);

// Copy assignment operator
  journal& operator=(const journal& old);

// Move assignment operator
  journal& operator=(journal&& old);

// Functions
// Setters and getters for Journal class variables
  double get_impact_factor(){return impact_factor;}
  int get_volume_number(){return volume_number;}
  std::shared_ptr<std::vector<string>> get_editor_names(){return editor_names;}
  std::shared_ptr<std::vector<string>> get_scope(){return scope;}
  void set_impact_factor(double new_impact_factor){impact_factor = new_impact_factor;}
  void set_volume_number(double new_volume_number){volume_number = new_volume_number;}
  void set_editor_names(std::shared_ptr<std::vector<string>> new_editor_names){editor_names = new_editor_names;}
  void set_scope(std::shared_ptr<std::vector<string>> new_scope){scope = new_scope;}

// Other functions for Journal class. Defined in cpp file.
  void print_information();
  void edit_information();
  std::string get_type(){return "Journal";}
  string data_output();

};

#endif