// Journal Class Functions
// This cpp file contains all the functions defined for the journal class.

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<sstream>
#include<algorithm>
#include "journal.h"

using std::string;

// State functions that are defined elsewhere
void string_stream_output_function(std::shared_ptr<std::vector<string>> vector_pointer);
void set_ptrvector_manual(std::shared_ptr<std::vector<string>> ptrVector, string ptrName);
void clear_screen();

// Copy Constructor
journal::journal(const journal& old): literature(old)
{
  editor_names = nullptr;
  scope = nullptr;

  impact_factor = old.impact_factor;
  volume_number = old.volume_number;

  if(old.editor_names)
    editor_names = std::make_shared<std::vector<string>>(*old.editor_names);
  if(old.scope)
    scope = std::make_shared<std::vector<string>>(*old.scope);
}

// Move Constructor
journal::journal(journal&& old)  
: literature(old)
{
  editor_names = old.editor_names;
  scope = old.scope;
  impact_factor = old.impact_factor;
  volume_number = old.volume_number;

  old.editor_names = nullptr;
  old.scope = nullptr;
}

// Copy Assignment
journal & journal::operator=(const journal& old) 
{
  if(&old == this) 
    return *this;
  
  literature::operator=(old);
  impact_factor = old.impact_factor;
  volume_number = old.volume_number;

  if (old.editor_names)
    editor_names = std::make_shared<std::vector<string>>(*old.editor_names);
  if (old.scope)
    scope = std::make_shared<std::vector<string>>(*old.scope);

  return *this;
}

// Move Assignment
journal& journal::operator=(journal&& old) 
{
  literature::operator=(std::move(old));
  std::swap(impact_factor, old.impact_factor);
  std::swap(volume_number, old.volume_number);
  std::swap(editor_names, old.editor_names);
  std::swap(scope, old.scope);

  return *this;
}

void journal::print_information()
{
  literature::print_information();
  std::cout<<"Number of Volumes: "<<volume_number<<std::endl;

// Create string stream to output editor names.
  std::cout<<"Editor names: ";
  string_stream_output_function(editor_names);

// Again, create the string stream for the scope
  std::cout<<"Scope: ";
  string_stream_output_function(scope);

  std::cout<<"Impact Factor: "<<impact_factor<<std::endl;
  std::cout<<std::endl;
}

void journal::edit_information()
{
  string input;
  int choice{0};
  clear_screen();

  do // Do While loop so it returns to the menu after completing task.
  {
    std::cout << "Editing Journal:"<<std::endl;
    std::cout << "1.Title "<<std::endl;
    std::cout << "2.Authors"<<std::endl;
    std::cout << "3.Editors"<<std::endl;
    std::cout << "4.Scope"<<std::endl;
    std::cout << "5.Impact Factor"<<std::endl;
    std::cout << "6.Volume Number"<<std::endl;
    std::cout << "7.Exit"<<std::endl;
    std::cout << "Choose an option (or 'q' to quit): ";
    std::getline(std::cin, input);

    if (input == "q")
      return; // Exit if q typed.

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
        set_ptrvector_manual(editor_names, "editor names");
        break;
      case 4:
        set_ptrvector_manual(scope, "scope");
        break;
      case 5:
        std::cout << "Current Impact Factor: " << impact_factor << std::endl;
        std::cout << "Enter new Impact Factor: ";
        while (true) 
        {
          if (!(std::cin >> impact_factor)) // Check if input can be converted to double/int
          {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear string stream
            std::cout << "Invalid input for price. Please enter a numeric value: ";
          } 
          else 
          {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            break;
          }
        }
        break;
      case 6:
        std::cout << "Current volume number: " << volume_number << std::endl;
        std::cout << "Enter new volume number: ";
        while (true) 
        {
          if (!(std::cin >> volume_number)) 
          {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input for price. Please enter a numeric value: ";
          } 
          else 
          {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            break;
          }
        }
        break;
      case 7:
        return;
      default:
        std::cout << "Invalid choice. Try again." << std::endl;;
    }
    clear_screen();
    std::cout<<"Edit applied."<<std::endl;
  } while (choice != 7);
} 

string journal::data_output() // For writing to a new data file.
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
  output_stream << "} {" << impact_factor << "} {" << volume_number << "} {";
  auto& editors_vector = *editor_names;
  for (auto it = editors_vector.begin(); it != editors_vector.end(); ++it) 
  {
    output_stream << *it;
    if (std::next(it) != editors_vector.end()) // Check if not the last element
      output_stream << ",";
  }
  output_stream << "} {";
  auto& scope_vector = *scope;
  for (auto it = scope_vector.begin(); it != scope_vector.end(); ++it) 
  {
    output_stream << *it;
    if (std::next(it) != scope_vector.end()) // Check if not the last element
      output_stream << ",";
  }
  output_stream << "}";

  return output_stream.str(); // Return result as a single line string for output.
}