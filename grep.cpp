#include "grep.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sstream>
#include <dirent.h>
#include <vector>
#include <chrono>       
#include <map>
#include <iterator>
#include <algorithm>
#include <thread> 


bool compare_dir(std::pair<std::string, int>&a,
                 std::pair<std::string, int>&b)
{
    return a.second > b.second; 
}

std::vector<std::pair<std::string, int>> sort_func(std::map<std::string, int>& M)
{
    
    std::vector<std::pair<std::string, int>> temp;

    for(auto &it : M)
        temp.push_back(it); 

    sort(temp.begin(), temp.end(), compare_dir); 

    return temp; 

}


        void Grep::set_directory(fs::path path)
        {
            directory_value = path;  

        }

        void Grep::set_word(std::string word)
        {
            searched_word = word; 
        }


        
        void Grep::set_log_file_name(std::string log_file_name)
        {

            log_f_name = log_file_name; 
        }


        void Grep::set_txt_file_name(std::string text_file_name)
        {

            text_f_name = text_file_name; 
        }


        void Grep::grep_func(std::vector<size_t> &results)
        {
            
    
    //std::vector<std::pair<std::string, int>>::iterator sortitr; 
      //  std::vector<int> res; 

      std::ofstream txt_file; 
      std::ofstream log_file;

      txt_file.open(text_f_name);
      log_file.open(log_f_name); 

    fs::path p = directory_value; 

    
    for (const auto  & entry : fs::recursive_directory_iterator(p))
        {   

            std::ifstream infile(entry.path()); 
            std::string curpath = entry.path(); 

             
            //int path_counter = 0; 
             while(getline(infile, line))
             {

                ++line_no; 
                auto pos = line.find(searched_word); 
                if (pos != std::string::npos)        // here we can now print the directories by returning the sorted map 
                    {                           // but i dont have time for that 
                        //word_count++; 
                        files_w_pattern++; 
                        txt_file << entry.path(); 
                        txt_file << ":" << line_no << ":" << line << std::endl; 
                        log_file << std::this_thread::get_id() << ": " << entry.path() << std::endl; 
                          m[curpath]++; 
                    }   
             }
            searched_files++; 
            

        }
      //sorted = sort_func(m); 


        txt_file.close(); 
   
        
        
         for(auto itr = m.begin(); itr != m.end(); ++itr)
            {
                patterns_number += itr->second; 
            }
         
            //std::cout << patterns_number << std::endl; 
            

        files_w_pattern = m.size();

        //std::cout << files_w_pattern << std::endl; 
    
    
    results.push_back(searched_files); 
    results.push_back(files_w_pattern); 
    results.push_back(patterns_number); 
    



        }


/*
void Grep::print_results()
{
std::cout << "Searched files: " << x << std::endl; 
std::cout << "Files with pattern: " << y << std::endl; 
std::cout << "Patterns_number: " << z << std::endl; 
std::cout << "Result file: " << text_f_name<< std::endl;
std::cout << "Log file: " <<  log_f_name  << std::endl; 
std::cout << "Used threads: " << n_of_threads << std::endl; 


}
*/

void Grep::helper()
{
        std::cout << "Grepx help: Please insert with the following format\n";
        std::cout << "Usage: " << "./grepex " << " [search_string] [-d][directory] [-l][log file] " 
                                        " [r][result file] [-t][threads]\n"; 
}

fs::path Grep::get_directory()
{
    return directory_value; 
}