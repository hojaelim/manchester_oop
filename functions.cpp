// Misc Functions
// This cpp file contains all the misc functions used that are not part of a class.
// This cpp file is part of the project.
// Author: Hojae Lim

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<sstream>
#include<algorithm>
#include "database.h"
#include "literature.h"
#include "book.h"
#include "thesis.h"
#include "journal.h"

using std::string;

void clear_screen() // Used to clear the terminal screen for immersion. Also centres to the menus.
{
  std::cout << "\033[2J\033[H";
}

void string_stream_output_function(const std::shared_ptr<std::vector<string>> vector_pointer) // Outputs vector elements in a string stream, with commas and point at the end.
{
  std::ostringstream output_stream;
  std::vector<string>::iterator vector_begin{(*vector_pointer).begin()};
  std::vector<string>::iterator vector_end{(*vector_pointer).end()};
  std::sort(vector_begin, vector_end);
  std::vector<string>::iterator vector_iterator;

  for(vector_iterator = vector_begin; vector_iterator<vector_end; ++vector_iterator)
  {
    output_stream << *vector_iterator;
    if(std::next(vector_iterator) != vector_end)
      output_stream<<", ";
    else
      output_stream<<".";
  }
  std::cout<< output_stream.str() << std::endl;
  output_stream.str("");
  output_stream.clear();
}

void set_ptrvector_manual(std::shared_ptr<std::vector<string>> ptr_vector, string ptr_name) // Used to set vector values.
{
  string input;

  std::cout<<"Current "<<ptr_name<<": ";
  string_stream_output_function(ptr_vector);

  std::cout<<"Please enter the "<<ptr_name<<" one at a time. Type q to stop entering."<<std::endl;
  ptr_vector->clear();
  while(true)
  {
    std::getline(std::cin, input);
    if(input == "q")
      break;
    ptr_vector->push_back(input);
  }
  ptr_vector->erase
  (
    std::remove_if(ptr_vector->begin(), ptr_vector->end(), 
    [](const std::string& s) 
    {
      return s.empty();
    }
    ), ptr_vector->end()
  );
}

std::vector<std::string> split(const std::string& input_string, char delimiter) // Used to split line inputs into categories
{
  std::stringstream input_ss(input_string);
  std::string item;
  std::vector<std::string> split_elements;
  while (getline(input_ss, item, delimiter))
    split_elements.push_back(item);
  return split_elements;
}

std::string trim(const std::string& trimming_string) // Used to trim the split strings into clean strings
{
  size_t first = trimming_string.find_first_not_of(" {");
  if (first == std::string::npos) 
    return "";
  size_t last = trimming_string.find_last_not_of(" }");
  return trimming_string.substr(first, (last - first + 1));
}

database read_data(const string file_path) // Used to read data and store them
{
  std::string line;
  database db;
  std::ifstream file(file_path);
  if (!file) 
  {
    std::cerr << "Could not open the file... Please check file name and format again." << std::endl;
    exit(1);
  }
  while (std::getline(file, line)) 
  {
    if (line.substr(0, 2) == "//") 
      continue;  // Skips any line starting with '//'
  
    std::vector<std::string> parts = split(line, '}');
    for (auto& part : parts) 
      part = trim(part);

    // Split the line depending on the literature type, then add to database
    if(parts[0] == "journal")
    {
      string temp_title = parts[1];
      std::vector<string> temp_author = split(trim(parts[2]), ',');
      int temp_volumenumber = std::stoi(parts[4]);
      std::vector<string> temp_editornames = split(trim(parts[5]), ',');
      std::vector<string> temp_scope = split(trim(parts[6]), ',');
      int temp_impactfactor = std::stoi(parts[3]);

      auto temp_journal = std::make_shared<journal>(temp_title, std::make_shared<std::vector<string>>(temp_author), temp_volumenumber, std::make_shared<std::vector<string>>(temp_editornames), std::make_shared<std::vector<string>>(temp_scope), temp_impactfactor); 
    
      db.add_entry(temp_journal);
    }
    else if(parts[0] == "book")
    {
      string temp_title = parts[1];
      std::vector<string> temp_author = split(trim(parts[2]), ',');
      string temp_publisher = parts[3];
      string temp_subject = parts[4];
      double temp_price = std::stod(parts[5]);

      auto temp_book = std::make_shared<book>(temp_title, std::make_shared<std::vector<string>>(temp_author), temp_publisher, temp_subject, temp_price);
      db.add_entry(temp_book);
    }
    else if(parts[0] == "thesis")
    {
      string temp_title = parts[1];
      std::vector<string> temp_author = split(trim(parts[2]), ',');
      string temp_supervisor = parts[3];
      string temp_university = parts[4];

      auto temp_thesis = std::make_shared<thesis>(temp_title, std::make_shared<std::vector<string>>(temp_author), temp_supervisor, temp_university);

      db.add_entry(temp_thesis);
    }
    else
    {
      std::cout<<"Invalid literature type detected... Skipping..."<<std::endl; // Skip any invalid literature types.
    }
  }
  file.close();
  return db;
}

void search_menu(database db) // Menu for searching to ease user experience.
{
  string option_select_string;
  int option_select;
  string search_input;
  database search_db;

  do
  {
    std::cout<<"Please Choose an Option (enter q to exit):"<<std::endl;
    std::cout<<"1. Search by Type"<<std::endl;
    std::cout<<"2. Search by Title"<<std::endl;
    std::cout<<"3. Search by Author"<<std::endl;
    std::cout<<"4. Exit"<<std::endl;

    std::getline(std::cin, option_select_string);

    if (option_select_string == "q")
      return;

    // Try and catch for inputted index number
    try 
    {
      option_select = std::stoi(option_select_string);
    }
    catch (const std::invalid_argument& e)
    {
      clear_screen();
      std::cout << "Invalid input. Please enter a valid index number." << std::endl;
      continue;
    } 
    catch (const std::out_of_range& e) 
    {
      clear_screen();
      std::cout << "Input out of range. Please enter a valid index number." << std::endl;
      continue;
    } 

    clear_screen();
    switch (option_select) 
    {
      case 1:
        std::cout<<"Please enter the search term (type in lower case): "<<std::endl;
        std::getline(std::cin, search_input);
        search_db = db.search_type(search_input);
        clear_screen();
        search_db.print_information();
        break;
      case 2:
        std::cout<<"Please enter the search term: "<<std::endl;
        std::getline(std::cin, search_input);
        search_db = db.search_title(search_input);
        clear_screen();
        search_db.print_information();
        break;
      case 3:
        std::cout<<"Please enter the search term: "<<std::endl;
        std::getline(std::cin, search_input);
        search_db = db.search_author(search_input);
        clear_screen();
        search_db.print_information();
        break;
      case 4:
        return;
      default:
        std::cout << "Invalid choice. Try again."<<std::endl;;
    }
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    clear_screen();
  }
  while(option_select != 4);
}
