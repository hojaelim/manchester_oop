// Book Class Functions
// This cpp file contains all the functions defined for the derived book class.

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<sstream>
#include<algorithm>
#include "book.h"

using std::string;
// State functions that are defined elsewhere
void string_stream_output_function(std::shared_ptr<std::vector<string>> vector_pointer);
void set_ptrvector_manual(std::shared_ptr<std::vector<string>> ptrVector, string ptrName);
void clear_screen();

// Copy Constructor
book::book(const book& old): literature(old)
{
  publisher = old.publisher;
  subject = old.subject;
  price = old.price;

}

// Move Constructor
book::book(book&& old)  
: literature(old)
{
  publisher = old.publisher;
  subject = old.subject;
  price = old.price;
}

// Copy Assignment
book & book::operator=(const book& old) 
{
  if(&old == this) 
    return *this;
  
  literature::operator=(old);
  publisher = old.publisher;
  subject = old.subject;
  price = old.price;
  return *this;
}

// Move Assignment
book& book::operator=(book&& old) 
{
  literature::operator=(std::move(old));
  std::swap(publisher, old.publisher);
  std::swap(subject, old.subject);
  std::swap(price, old.price);

  return *this;
}

void book::print_information()
{
  literature::print_information(); // Use base class function
  std::cout<<"Publisher: "<<publisher<<std::endl;
  std::cout<<"Subject: "<<subject<<std::endl;
  std::cout<<"Price: "<<price<<std::endl;
  std::cout<<std::endl;
}

void book::edit_information()
{
  string input;
  int choice{0};
  clear_screen();

  do // Do While loop so it returns to the menu after completing task.
  {
    std::cout << "Editing Book:"<<std::endl;
    std::cout << "1.Title "<<std::endl;
    std::cout << "2.Authors"<<std::endl;
    std::cout << "3.Publisher"<<std::endl;
    std::cout << "4.Subject"<<std::endl;
    std::cout << "5.Price"<<std::endl;
    std::cout << "6.Exit"<<std::endl;
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
        std::cout << "Current Publisher: " << publisher << std::endl;
        std::cout << "Enter new publisher: ";
        std::getline(std::cin, publisher);
        break;
      case 4:
        std::cout << "Current Subject: " << subject << std::endl;
        std::cout << "Enter new subject: ";
        std::getline(std::cin, subject);
        break;
      case 5:
        std::cout << "Current Price: " << price << std::endl;
        std::cout << "Enter new price: ";
        while (true) 
        {
          if (!(std::cin >> price)) 
          {
            std::cin.clear(); // Clear error flag
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
      case 6:
        return;
      default:
        std::cout << "Invalid choice. Try again."<<std::endl;;
    }
    clear_screen();
    std::cout<<"Edit applied."<<std::endl;
  } while (choice != 6); 
} 

string book::data_output() // Used to write the data file
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
  output_stream << "} {" << publisher << "} {" << subject << "} {" << price << "}";
  return output_stream.str(); // Return result as a single line string for output.
}