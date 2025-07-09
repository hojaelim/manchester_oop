// Literature Class Functions
// This cpp file contains all the functions defined for the base literature class.

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<sstream>
#include<algorithm>
#include "literature.h"

using std::string;

// State functions that are defined elsewhere
void string_stream_output_function(std::shared_ptr<std::vector<string>> vector_pointer);
void set_ptrvector_manual(std::shared_ptr<std::vector<string>> ptrVector, string ptrName);

// Copy Constructor
literature::literature(const literature& old)
{
  author = nullptr;
  title = old.title;
  literature_type = old.literature_type;

  if(old.author)
    author = std::make_shared<std::vector<string>>(*old.author);
}

// Move Constructor
literature::literature(literature&& old) 
{
  author = old.author;
  title = old.title;
  literature_type = old.literature_type;

  old.author = nullptr;
}

// Copy Assignment
literature & literature::operator=(const literature& old) 
{
  if(&old == this) 
    return *this;

  title = old.title;
  literature_type = old.literature_type;

  if (old.author)
    author = std::make_shared<std::vector<string>>(*old.author);

  return *this;
}

// Move Assignment
literature& literature::operator=(literature&& old) 
{
  std::swap(author, old.author);
  std::swap(literature_type, old.literature_type);
  std::swap(title, old.title);

  return *this;
}

void literature::print_information() // Used as a inherited function
{
  std::cout<<"Literature Type: "<<literature_type<<std::endl;
  std::cout<<"Title: "<<title<<std::endl;
  std::cout<<"Author: ";
  string_stream_output_function(author);
}
