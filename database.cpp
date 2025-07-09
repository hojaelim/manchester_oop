// Database Functions
// This cpp file contains all the functions defined for the database class.

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<sstream>
#include<fstream>
#include<algorithm>
#include "literature.h"
#include "book.h"
#include "thesis.h"
#include "journal.h"
#include "database.h"

using std::string;

// State functions that are defined elsewhere
void clear_screen(); // Declared so that it can be used...

// Copy Constructor
database::database(const database& old) 
{
  for(const auto& entry : old.entries) 
  {
    entries.push_back(std::make_pair(entry.first, entry.second));
  }
  entry_index = old.entry_index;
}

// Move Constructor
database::database(database&& old) 
{
  entries = old.entries;
  entry_index = old.entry_index;

  old.entries.clear();
}

// Copy Assignment
database & database::operator=(const database& old) 
{
  if(&old == this) 
    return *this;

  entries.clear();

  entry_index = old.entry_index;

  for (const auto& entry : old.entries) 
  {
    entries.push_back(std::make_pair(entry.first, entry.second));
  }
  return *this;
}

// Move Assignment
database& database::operator=(database&& old) 
{
  std::swap(entries, old.entries);
  std::swap(entry_index, old.entry_index);

  return *this;
}

void database::add_entry(std::shared_ptr<literature> new_literature) // For when programme automatically adds entries to the database.
{
  entries.push_back(std::make_pair(entry_index, new_literature));
  entry_index++; // Add to entry index so all entries are indexed chronologically
}

void database::add_manual_entry() // For when user wants to add entry into the database.
{
  string literature_type_input;
  int literature_type_index;
  string new_title;
  std::shared_ptr<std::vector<string>> new_authors = std::make_shared<std::vector<string>>(); 
  string new_author_input;

  enum literature_type 
  {
    BOOK = 1,
    THESIS = 2,
    JOURNAL = 3 
  }; 

  bool valid_input(false);
  while(!valid_input) // Loop so that if the input is not valid, it asks again to type in correct index
  {
    std::cout << "What type of literature would you like to add? (Enter q to cancel)" << std::endl;
    std::cout << "1: Book" << std::endl;
    std::cout << "2: Thesis" << std::endl;
    std::cout << "3: Journal" << std::endl;
    std::getline(std::cin, literature_type_input);

    if (literature_type_input == "q") 
    {
      std::cout << "Operation cancelled. Returning to main menu." << std::endl;
      return; 
    }

    try 
    {
      literature_type_index = std::stoi(literature_type_input);
      valid_input = true; // Valid input, break the loop
    } 
    catch (const std::invalid_argument& e) 
    {
      std::cout << "Invalid input, please enter a valid index number." << std::endl;
    } 
    catch (const std::out_of_range& e) 
    {
      std::cout << "Input out of range, please enter a valid index number." << std::endl;
    }

    switch(literature_type_index)
    {

      case BOOK:
      {
        string new_publisher;
        string new_subject;
        string new_price_string;
        double new_price;
        bool valid_price = false;

        std::cout<<"Please enter the title:"<<std::endl;
        std::getline(std::cin, new_title);

        std::cout<<"Please enter the authors one at a time. Type q to stop entering authors."<<std::endl;
        while(true)
        {
          std::getline(std::cin, new_author_input);
          if(new_author_input == "q")
            break;
          new_authors->push_back(new_author_input);
        }

        std::cout<<"Please enter the publisher:"<<std::endl;
        std::getline(std::cin, new_publisher);
        std::cout<<"Please enter the subject:"<<std::endl;
        std::getline(std::cin, new_subject);

        while (!valid_price) 
        {
          std::cout << "Please enter the price:" << std::endl;
          std::getline(std::cin, new_price_string);
          try 
          {
            new_price = std::stod(new_price_string);
            valid_price = true;
          } 
          catch (const std::invalid_argument& e) 
          {
            std::cout << "Invalid input. Please enter a numeric value for the price." << std::endl;
          } 
          catch (const std::out_of_range& e) 
          {
            std::cout << "Input out of range. Please enter a more reasonable value for the price." << std::endl;
          }
        }

        std::shared_ptr<book> new_literature = std::make_shared<book>(new_title, new_authors, new_publisher, new_subject, new_price);
        entries.push_back(std::make_pair(entry_index, new_literature));
        entry_index++;  
        valid_input = true;
        break;
      }
      case THESIS:
      {
        string new_supervisor;
        string new_university;

        std::cout<<"Please enter the title:"<<std::endl;
        std::getline(std::cin, new_title);

        std::cout<<"Please enter the authors one at a time. Type q to stop entering authors."<<std::endl;
        while(true)
        {
          std::getline(std::cin, new_author_input);
          if(new_author_input == "q")
            break;
          new_authors->push_back(new_author_input);
        }

        std::cout<<"Please enter the university:"<<std::endl;
        std::getline(std::cin, new_university);
        std::cout<<"Please enter the supervisor:"<<std::endl;
        std::getline(std::cin, new_supervisor);

        std::shared_ptr<thesis> new_literature = std::make_shared<thesis>(new_title, new_authors, new_supervisor, new_university);
        entries.push_back(std::make_pair(entry_index, new_literature));
        entry_index++;  
        valid_input = true;
        break;
      }
      case JOURNAL:
      {
        double new_impact_factor;
        int new_volume_number;
        std::shared_ptr<std::vector<string>> new_editor_names = std::make_shared<std::vector<string>>(); 
        string new_editor_input;
        std::shared_ptr<std::vector<string>> new_scope = std::make_shared<std::vector<string>>(); 
        string new_scope_input;
        bool valid_impact_factor{false};
        bool valid_volume_number{false};

        std::cout<<"Please enter the title:"<<std::endl;
        std::getline(std::cin, new_title);

        std::cout<<"Please enter the authors one at a time. Type q to stop entering authors."<<std::endl;
        while(true)
        {
          std::getline(std::cin, new_author_input);
          if(new_author_input == "q")
            break;
          new_authors->push_back(new_author_input);
        }

        std::cout<<"Please enter the editor names one at a time. Type q to stop entering."<<std::endl;
        while(true)
        {
          std::getline(std::cin, new_editor_input);
          if(new_editor_input == "q")
            break;
          new_editor_names->push_back(new_editor_input);
        }

        std::cout<<"Please enter the scope one at a time. Type q to stop entering."<<std::endl;
        while(true)
        {
          std::getline(std::cin, new_scope_input);
          if(new_scope_input == "q")
            break;
          new_scope->push_back(new_scope_input);
        }

        std::string input;

        while (!valid_impact_factor) 
        {
          std::cout<<"Please enter the impact factor:"<<std::endl;
          std::getline(std::cin, input);
          try 
          {
            new_impact_factor = std::stoi(input);
            valid_impact_factor = true;
          } 
          catch (const std::invalid_argument& e) 
          {
            std::cout << "Invalid input. Please enter a integer value for the impact factor." << std::endl;
          } 
          catch (const std::out_of_range& e) 
          {
            std::cout << "Input out of range." << std::endl;
          }
        }

        while (!valid_volume_number) 
        {
          std::cout<<"Please enter the volume number:"<<std::endl;
          std::getline(std::cin, input);
          try 
          {
            new_volume_number = std::stoi(input);
            valid_volume_number = true;
          } 
          catch (const std::invalid_argument& e) 
          {
            std::cout << "Invalid input. Please enter a integer value for the volume number." << std::endl;
          } 
          catch (const std::out_of_range& e) 
          {
            std::cout << "Input out of range." << std::endl;
          }
        }

        std::shared_ptr<journal> new_literature = std::make_shared<journal>(new_title, new_authors, new_volume_number, new_editor_names, new_scope, new_impact_factor);
        entries.push_back(std::make_pair(entry_index, new_literature));
        entry_index++;  
        valid_input = true;
        break;
    
      }
      default:
        std::cout<<"Invalid option. Please try again."<<std::endl;
        return;
    }
  }

  std::cout<<"Entry added successfully."<<std::endl;
}

void database::add_search_entry(const std::pair<int, std::shared_ptr<literature>> searched_entry)
{
  entries.push_back(searched_entry); // Different from add_entry as we want to keep the same index number, so that users can choose to modify the index without looking at all results again.
}

database database::search_title(const string title_input) // Search by title
{
  std::vector<std::pair<int, std::shared_ptr<literature> >> results;
  database title_searched_database;
  for(auto &entry : entries)
  {
    if((entry.second)->get_title() == title_input)
      results.push_back(entry);
  }

  for(auto searched_entry : results)
    title_searched_database.add_search_entry(searched_entry);

  return title_searched_database;
}

database database::search_author(const string author_input) // Search by author
{
  std::vector<std::pair<int, std::shared_ptr<literature> >> results;
  database author_searched_database;
  for(auto &entry : entries)
  {
    auto authors = entry.second->get_author();
    for (auto &author : *authors) // Allows for it to search individual authors in the author list.
    {
      if(author == author_input)
        results.push_back(entry);
    }
  }
  for(auto searched_entry : results)
    author_searched_database.add_search_entry(searched_entry);

  return author_searched_database;
}

database database::search_type(const string type_input) // Search by type.
{
  std::vector<std::pair<int, std::shared_ptr<literature> >> results;
  database type_searched_database;
  for(auto &entry : entries)
  {
    if((entry.second)->get_type() == type_input) // Did not specify types into books, journal, thesis as this makes it more flexible for further literature implementations.
      results.push_back(entry);
  }

  for(auto searched_entry : results)
    type_searched_database.add_search_entry(searched_entry);

  return type_searched_database;
}

void database::print_information() // Prints information on screen individually, for a cleaner look in case the database size is large.
{
  int page_index = 0;
  string command;

  if(entries.empty())
  {
    std::cout<<"No entries have been found."<<std::endl;
    return ;
  }

  while (true) 
  {
    if (page_index >= 0 && page_index < entries.size()) 
    {
      std::cout << "Index number " << page_index + 1 <<" of "<<entries.size()<< std::endl;
      ((entries[page_index]).second)->print_information();
    }

    std::cout << "Enter n for next, p for previous, q to quit: ";
    std::getline(std::cin, command);

    if (command == "n" && page_index < entries.size() - 1) // Prints succeeding element
    { 
      page_index++;
      clear_screen();
    }
    else if (command == "n" && page_index == entries.size() - 1) // Doesnt move page if last element in database
    {
      clear_screen();
      std::cout<<"Reached end of page."<<std::endl;
    }
    else if (command == "p" && page_index > 0) // Prints preceding element
    {
      page_index--;
      clear_screen();
    }
    else if (command == "p" && page_index == 0) // Doesnt move page if first element in database
    {
      clear_screen();
      std::cout<<"Reached start of page."<<std::endl;
    }
    else if (command == "q")
    {
      clear_screen();
      break;
    }
    else
    {
      clear_screen();
      std::cout<<"Invalid input. Please try again."<<std::endl;
      continue;
    }
  }
}

void database::delete_entry()
{
  clear_screen();

  string string_input;
  int deleting_index;
  bool valid_input = false;

  while(valid_input == false)
  {
    std::cout<<"Please enter the index number of the entry you would like to delete (type q to cancel): "<<std::endl;
    std::getline(std::cin, string_input);

    if(string_input == "q")
      return ;

    try // Try catch to check if given index input is valid
    {
      deleting_index = std::stoi(string_input);
      valid_input = true;
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << "Invalid input. Please enter a valid index number." << std::endl;
    } 
    catch (const std::out_of_range& e) 
    {
      std::cout << "Input out of range. Please enter a valid index number." << std::endl;
    }  
  }

  for(auto i = entries.begin(); i != entries.end(); ++i)
  {
    if(i->first == deleting_index)
    {
      entries.erase(i);
      std::cout<<"Entry with index "<<deleting_index<<" has been removed."<<std::endl;
      for(auto j = i; j != entries.end(); ++j) // Shifts index numbers of succeeding entries
        {
          j->first--;
        }

      std::cout<<"Subsequent index numbers have been shifted."<<std::endl;
      return;
    }
  }
  std::cout<<"No entry with index "<<deleting_index<<" has been found."<<std::endl;
}

void database::edit_entry()
{
  clear_screen();

  string string_input;
  int editing_index;
  bool valid_input = false;
  while(valid_input == false)
  {
    std::cout<<"Please enter the index number of the entry you would like to edit (enter q to cancel): "<<std::endl;
    std::getline(std::cin, string_input);

    if(string_input == "q")
    {
      std::cout<<"Edit Operation Cancelled by User."<<std::endl;
      return ;
    }

    try  // Try catch to check if index number typed is valid.
    {
      editing_index = std::stoi(string_input);
      valid_input = true;
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << "Invalid input. Please enter a valid index number." << std::endl;
    } 
    catch (const std::out_of_range& e) 
    {
      std::cout << "Input out of range. Please enter a valid index number." << std::endl;
    }  
  }
  
  for(auto i = entries.begin(); i != entries.end(); ++i) // Call edit_information of respective class for a given index.
  {
    if(i->first == editing_index)
    {
     (i->second)->edit_information();
    }
  }
  std::cout<<std::endl;
  std::cout<<"Edit applied successfully."<<std::endl;

}

void database::average_book_price() // Calculates average book price of elements stored in database.
{
  double price_sum(0);
  int book_count(0);
  double average_price;
  for(auto &entry : entries)
  {
    book* casted_book = dynamic_cast<book*>(entry.second.get());
    if(casted_book != nullptr)
    {
      price_sum += casted_book->get_price();
      book_count++;
    }
  }
  average_price = (book_count > 0) ? (price_sum / book_count) : 0;
  std::cout<<"There is a total of "<<book_count<<" books."<<std::endl;
  std::cout << std::fixed << std::setprecision(2);
  std::cout<<"The average price of books are "<<average_price<<"."<<std::endl;
  std::cout.unsetf(std::ios_base::fixed);
  std::cout<<"\n\n\n"<<std::endl;

}

void database::write_data() // Writes data to a new/existing file, using data_output of respective literature class.
{
  string filename;
  std::cout<<"Please enter the file name and format you wish to save in."<<std::endl;
  std::getline(std::cin, filename);

  std::ofstream file_output(filename);

  if (!file_output) 
  {
    std::cerr << "Failed to open file for writing."<<std::endl;
    return;
  }

  for (const auto& entry : entries) 
    file_output << entry.second->data_output() << std::endl;

  file_output.close();
  std::cout<<std::endl;
  std::cout<<"File writing complete."<<std::endl;
}
