#include "grep.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>    


using namespace std::chrono;



int main(int argc, char* argv[])
{

auto start = high_resolution_clock::now();
Grep grep_obj; 
std::vector<size_t> results; // getting the results by reference rather than getter inside the object, 


    std::vector<std::thread> threads; 

    // setting up the flags 
    std::string flag1;
    std::string flag2;
    std::string flag3;
    std::string flag4;
    std::string d_flag = "-d"; 
    std::string l_flag = "-l";
    std::string r_flag = "-r";
    std::string t_flag = "-t"; 

    size_t num_of_threads{4}; 
    std::string sword; 
    
    fs::path cwd = fs::current_path();

  
    if(argc % 2 == 1) // if ./grepex executed once, the following instructions will be prompted 
    {   
        grep_obj.helper(); 
        return 1; 
    }


    if(argc > 1)
        {
            sword = argv[1];
            grep_obj.set_word(sword); 
        }
   

    if (argc == 2)
    {    
        //grep_obj.set_word(argv[1]); 
        grep_obj.set_directory(cwd); 

        for(int i = 0; i < num_of_threads; i++)
            {
                threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results)); 

            }

        for(auto & thread : threads)
            { 
        thread.join(); 
            }
    }
    else if (argc == 4)
    {   
        // ctpl::thread_pool p(num_of_threads); 
        
         
        flag1 = argv[2]; 

        if(flag1 == d_flag)
        {
            //sword = argv[1];
            //grep_obj.set_word(sword);
            grep_obj.set_directory(argv[3]);
            

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                   threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results));
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }      
        }
        else if(flag1 == l_flag)
            {
                //grep_obj.set_word(sword);
                grep_obj.set_directory(cwd.string());                 
                grep_obj.set_log_file_name(argv[3]);
               for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                     threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results));
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

            }
        else if(flag1 == r_flag)
            {
                //grep_obj.set_word(sword); 
                grep_obj.set_directory(cwd);
                grep_obj.set_txt_file_name(argv[3]); 

                for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                     threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results));
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

            }
        else if(flag1 == t_flag) // I DON'T KNOW THIS YET 
            {
                //grep_obj.set_word(sword); 
                grep_obj.set_directory(cwd); 
                num_of_threads = atoi(argv[3]); 
                for( size_t i = 0; i < num_of_threads; i++) // cwd.string() is an r-value already,
                    {                                       // but we need to send the others as std::ref 
                        threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results));
                    }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
    
            }
        else
        {
          grep_obj.helper(); 
            return 1; 

        }
    }
    else if (argc == 6)
     {
        flag1 = argv[2];
        flag2 = argv[4]; 
        if(flag1 == d_flag && flag2 == l_flag)
        {   
            //grep_obj.set_word(sword);
            grep_obj.set_directory(argv[3]);
            grep_obj.set_log_file_name(argv[5]);

  
            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results));
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
            

        }
        else if(flag1 == l_flag && flag2 == r_flag)
        {
            //grep_obj.set_word(sword);
            grep_obj.set_directory(cwd);
            grep_obj.set_log_file_name(argv[3]);
            grep_obj.set_txt_file_name(argv[5]);

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                   threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results));
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

        }
        else if(flag1 == r_flag && flag2 == t_flag)
        {  
            grep_obj.set_word(sword);
            grep_obj.set_directory(cwd);
            grep_obj.set_txt_file_name(argv[3]);
            num_of_threads = atoi(argv[5]); 

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                   threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
        }
        else if(flag1 == d_flag && flag2 == r_flag)
        {     
                //grep_obj.set_word(sword);
                grep_obj.set_directory(argv[3]);
                grep_obj.set_txt_file_name(argv[5]);

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

            }
        
    }
    else if(argc == 8)
    {   
        flag1 = argv[2];
        flag2 = argv[4];
        flag3 = argv[6];
        
        if(flag1 == d_flag && flag2 == l_flag && flag3 == r_flag)
        {
                //grep_obj.set_word(sword);
                grep_obj.set_directory(argv[3]);
                grep_obj.set_log_file_name(argv[5]);
                grep_obj.set_txt_file_name(argv[7]); 

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                   threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

        }
        else if(flag1 == l_flag && flag2 == r_flag && flag3 == t_flag)
        {
                //grep_obj.set_word(sword);
                grep_obj.set_directory(cwd);
                grep_obj.set_log_file_name(argv[3]);
                grep_obj.set_txt_file_name(argv[5]); 

            num_of_threads = atoi(argv[7]);

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                   threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results));  
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
            
        }
        else if(flag1 == d_flag && flag2 == r_flag && flag3 == t_flag)     
        {
                //grep_obj.set_word(sword);
                grep_obj.set_directory(argv[3]);
                grep_obj.set_txt_file_name(argv[5]); 
                grep_obj.set_log_file_name(argv[7]);
              
        
            num_of_threads = atoi(argv[7]); 

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
        }
        else
        { 
            grep_obj.helper();
            return 1; 
        }

    }
    else if (argc == 10)
    {
        flag1 = argv[2];
        flag2 = argv[4];
        flag3 = argv[6];
        flag4 = argv[8];
        
        if(flag1 == d_flag && flag2 == l_flag && flag3 == r_flag && flag4 == t_flag)
        {       

                //grep_obj.set_word(sword);
                grep_obj.set_directory(argv[3]); 
                grep_obj.set_log_file_name(argv[5]);
                grep_obj.set_txt_file_name(argv[7]);
            
                num_of_threads = atoi(argv[9]);

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(&Grep::grep_func, grep_obj, std::ref(results));
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
        }
        else 
        {
            grep_obj.helper(); 
            return 1; 
        }

    }
    else{
        grep_obj.helper();
        return 1; 
    }

auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);

std::cout << "Searched files: " << results.at(0) << std::endl; 
std::cout << "Files with pattern: " << results.at(1) << std::endl; 
std::cout << "Patterns_number: " << results.at(2) << std::endl; 
std::cout << "Number of Threads: " << num_of_threads << std::endl; 
std::cout << "Elapsed time: " << duration.count() << "[ms]" << std::endl;

return 0; 

}