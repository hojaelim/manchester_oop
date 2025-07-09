// Project
// This is the main file for the literature catalogue project for Object-Oriented Programming in C++.
// The literature class types are stored in their respective header files, and their functions in their respective cpp file.
// All other functions are stored in the functions.cpp file.
// An example data file is provided with data.dat. The programme will run best by following the formatting provided.
// Please compile using: g++-11 -std=c++17 -fdiagnostics-color=always -g main.cpp functions.cpp database.cpp literature.cpp book.cpp thesis.cpp journal.cpp -o lit_cat
// And run the subsequent lit_cat file.
// Author: Hojae Lim
// Date: 8/5/2024

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

// State functions that are defined elsewhere
database read_data(string file_path);
void main_menu(database db, string filename);
void clear_screen();
void search_menu(database db);

int main()
{
  string filename;

  std::cout<<"Please type the name of the data file (including file format): ";
  std::getline(std::cin, filename);

  database new_database = read_data(filename);

  clear_screen();
  string option_select_string;
  int option_select(0);

  do // Print Main Menu and choose functionalities.
  {
    std::cout<<"Welcome to the Literary Catalogue Viewer and Editor."<<std::endl;
    std::cout<<"Author: Hojae Lim"<<std::endl;
    std::cout<<"You are currently viewing "<<filename<<std::endl;
    std::cout<<"Please Choose an Option (enter q to exit):"<<std::endl;
    std::cout<<"1. View all Entries"<<std::endl;
    std::cout<<"2. Add an Entry"<<std::endl;
    std::cout<<"3. Edit an Entry"<<std::endl;
    std::cout<<"4. Delete an Entry"<<std::endl;
    std::cout<<"5. Get the Average Book Price"<<std::endl;
    std::cout<<"6. Search Entries"<<std::endl;
    std::cout<<"7. Save Current Entries"<<std::endl;  
    std::cout<<"8. Exit"<<std::endl;

    std::getline(std::cin, option_select_string);

    if (option_select_string == "q")
      return 0;

    // try and catch to see if input is valid.
    try 
    {
      option_select = std::stoi(option_select_string);
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

    clear_screen();
    switch (option_select) 
    {
      case 1:
        new_database.print_information(); // Print information screen
        break;
      case 2:
        new_database.add_manual_entry(); // Options to add entry
        break;
      case 3:
        new_database.edit_entry(); // Option menu to edit entry
        break;
      case 4:
        new_database.delete_entry(); // Delete entry
        break;
      case 5:
        new_database.average_book_price(); // Print average book price
        break;
      case 6:
        search_menu(new_database); // Search menu for the database
        break;
      case 7:
        new_database.write_data(); // Write data to new file
        break;
      case 8:
        return 0; // Exit programme.
      default:
        std::cout << "Invalid choice. Try again."<<std::endl;;
    }
    std::cout << "Press Enter to continue..."; // To make sure programme doesnt fall into loop.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
    clear_screen();
  }
  while(option_select != 8);

  return 0;
}
