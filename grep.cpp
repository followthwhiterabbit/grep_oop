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
#include <set>

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

            std::ofstream txt_file; 
            std::ofstream log_file;

            txt_file.open(text_f_name);
            log_file.open(log_f_name); 

            fs::path p = directory_value; 

    
            for (const auto  & entry : fs::recursive_directory_iterator(p))
            {   
            
            std::ifstream infile(entry.path()); 
            std::string curpath = entry.path(); 
            std::stringstream ss; 

             ss << std::this_thread::get_id(); 
             uint64_t id_variable = std::stoull(ss.str());  

             mapthr2str.insert(std::make_pair(id_variable, entry.path())); 
             
                while(getline(infile, line))
                {  
                /*
                ss << std::this_thread::get_id(); 
                uint64_t id_variable = std::stoull(ss.str());  
                */
                ++line_no; 

                auto pos = line.find(searched_word); 

                //log_file << std::this_thread::get_id() << ": " << entry.path() << std::endl; 
                maplog.insert(std::pair<std::string, uint64_t>(curpath, id_variable)); 
                
                if (pos != std::string::npos)        
                    {                           
                        files_w_pattern++; 
                        txt_file << entry.path(); 
                        txt_file << ":" << line_no << ":" << line << std::endl; 
                        
                          m[curpath]++; 
 
                    }   
                }
            searched_files++; 
  

            }


      sorted = sort_func(m); 

        for(auto itr = maplog.begin(); itr != maplog.end(); itr++)
            {
                log_file << itr->second << ": " << itr->first << std::endl; 
            }

        /*

        for(size_t i = 0; i < vpair.size() / 4; i++)
            {
                for(size_t j = i + 1; j < vpair.size(); j++)
                    {    
                        if (vpair[i].first == vpair[j].first)
                            {
                                log_file << ": " << vpair[i].second << ", " << vpair[j].second << std::endl;
                                
                            }
                    }
            }
        */ 
       




        /*
            // DIRECTORIES ARE SORTED BY THEIR PATTERN NUMBERS 
        for(auto sortitr = sorted.begin(); sortitr != sorted.end(); sortitr++)
            {
                std::cout << sortitr->first << " " << sortitr->second << std::endl; 
                txt_file << sortitr->first << std::endl;             

            }
     
        */ 


       /*   
        

        for(std::multimap<uint64_t, std::string>::iterator it = mapthr2str.begin(); it != mapthr2str.end(); ++it)
            {

                std::cout << (*it).first << " " << (*it).second << '\n'; 
                //log_file << (*it).first << ": " << (*it).second << '\n'; 
            }
        
        */ 

       /*
       
        for(auto it = thread_ids.begin(); it != thread_ids.end(); it++)
        {
            log_file << *it << ": " << std::endl; 
    
        }
    
        */          

        txt_file.close(); 
        log_file.close(); 

        
         for(auto itr = m.begin(); itr != m.end(); ++itr)
            {
                patterns_number += itr->second; 
            }
         

        files_w_pattern = m.size();

    results.push_back(searched_files); 
    results.push_back(files_w_pattern); 
    results.push_back(patterns_number); 

        }


void Grep::helper()
{
        std::cout << "Grepx help: Please insert with the following format\n";
        std::cout << "Usage: " << "./grepex " << " [search_string] [-d][directory] [-l][log file] " 
                                        " [r][result file] [-t][threads]\n"; 
}


std::string Grep::get_log_file_name()
{
    return log_f_name; 
}

std::string Grep::get_txt_file_name()
{
    return text_f_name; 
}


