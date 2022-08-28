#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>



namespace fs = std::filesystem; 


class Grep
{
    public:
        Grep(std::string word)
            : searched_word(word)
        {

        } 
        ~Grep()
        {

        }
        void set_directory(fs::path path);
        fs::path get_directory();
        void set_log_file_name(std::string log_file_name);
        void set_txt_file_name(std::string text_file_name);
        std::string get_log_file_name();
        std::string get_txt_file_name(); 
        void grep_func(std::vector<size_t> &results);
        void helper(); 

    private:
        
        std::string searched_word; 
        std::string log_f_name{"grepex.log"}; 
        std::string text_f_name{"grepex.txt"}; 


        size_t patterns_number{0}; 
        size_t searched_files{0}; 
        size_t files_w_pattern{0};

        fs::path directory_value; 
        std::map<int, int>::iterator itr;
        std::vector<std::pair<std::string, int>>::iterator sortitr; 
        std::map<std::string, int> m;
        std::vector<std::pair<std::string, int>> sorted; 
        std::multimap<uint64_t, std::string> mapthr2str; 
        std::set<uint64_t> thread_ids; 

         size_t line_no = 0; 
        size_t word_count = 0; 
        std::string line;   
};