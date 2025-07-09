// Thesis Class Functions
// This cpp file contains all the functions defined for the derived thesis class.

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<sstream>
#include<algorithm>
#include "thesis.h"

using std::string;

// State functions that are defined elsewhere
void string_stream_output_function(std::shared_ptr<std::vector<string>> vector_pointer);
void set_ptrvector_manual(std::shared_ptr<std::vector<string>> ptrVector, string ptrName);
void clear_screen();

// Copy Constructor
thesis::thesis(const thesis& old): literature(old)
{
  supervisor = old.supervisor;
  university = old.university;
}

// Move Constructor
thesis::thesis(thesis&& old)  
: literature(old)
{
  supervisor = old.supervisor;
  university = old.university;
}

// Copy Assignment
thesis & thesis::operator=(const thesis& old) 
{
  if(&old == this) 
    return *this;
  
  literature::operator=(old);
  supervisor = old.supervisor;
  university = old.university;

  return *this;
}

// Move Assignment
thesis& thesis::operator=(thesis&& old) 
{
  literature::operator=(std::move(old));
  std::swap(supervisor, old.supervisor);
  std::swap(university, old.university);

  return *this;
}

void thesis::print_information()
{
  literature::print_information();
  std::cout<<"Supervisor: "<<supervisor<<std::endl;
  std::cout<<"University: "<<university<<std::endl;
  std::cout<<std::endl;
}

void thesis::edit_information()
{
  string input;
  int choice{0};
  clear_screen();

  do  // Do While loop so it returns to the menu after completing task.
  {
    std::cout << "Editing Thesis:"<<std::endl;
    std::cout << "1.Title "<<std::endl;
    std::cout << "2.Authors"<<std::endl;
    std::cout << "3.Supervisor"<<std::endl;
    std::cout << "4.University"<<std::endl;
    std::cout << "5.Exit"<<std::endl;
    std::cout << "Choose an option (or 'q' to quit): ";
    std::getline(std::cin, input);

    if (input == "q") // Exit if q typed.
      return;

    try // Try catch to check if input valid.
    {
      choice = std::stoi(input);
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << "Invalid input. Please enter a valid index number." << std::endl;
      continue;
    } 
    catch (const std::out_of_range& e) 
    {
      std::cout << "Input out of range. Please enter a valid index number." << std::endl;
      continue;
    }  

    switch (choice) 
    {
      case 1:
        std::cout << "Current Title: " << title << std::endl;
        std::cout << "Enter new title: ";
        std::getline(std::cin, title);
        break;
      case 2:
        set_ptrvector_manual(author, "author");
        break;
      case 3:
        std::cout << "Current Supervisor: " << supervisor << std::endl;
        std::cout << "Enter new supervisor: ";
        std::getline(std::cin, supervisor);
        break;
      case 4:
        std::cout << "Current University: " << university << std::endl;
        std::cout << "Enter new university: ";
        std::getline(std::cin, university);
        break;
      case 5:
        return;
      default:
        std::cout << "Invalid choice. Try again." << std::endl;
    }
    clear_screen();
    std::cout<<"Edit applied."<<std::endl;
  } while (choice != 5);
} 

string thesis::data_output() // For writing to a new data file.
{
  std::stringstream output_stream;
  output_stream<<"{book} {"<<title<<"} {";
  auto& authors_vector = *author;
  for (auto it = authors_vector.begin(); it != authors_vector.end(); ++it) 
  {
    output_stream << *it;
    if (std::next(it) != authors_vector.end()) // Check if not the last element
      output_stream << ",";
  }
  output_stream << "} {" << supervisor << "} {" << university << "}";
  return output_stream.str(); // Return result as a single line string for output.
}