#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "SchedulerManager.h"

SchedulerManager::SchedulerManager()
{
    config_kvs map_scheduler = {
        // maps string to corresponding int as representation when parsing config.txt
        {"fcfs", 0},
        {"rr", 1},
        {"sjf", 2}
    };

    // https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c
    std::fstream is_file("config.txt", std::ios::in | std::ios::out | std::ios::app);

    std::string line;
    while( std::getline(is_file, line) )
    {
        std::istringstream is_line(line);
        std::string key;
        if( std::getline(is_line, key, ' ') )
        {
            std::string value;
            if( std::getline(is_line, value) ) {
                if (key == "scheduler") {
                    this->config[key] = map_scheduler[value];
                } else {
                    this->config[key] = std::stoi(value);
                }
                // std::cout << key << ": " << value << "\n";
            }
        }
    }

    // If you want to check what the contents of config are
    // for (const std::pair<const String, int>& n : config){
    //     std::cout << n.first << ": " << n.second << "\n";
    // }
    is_file.close();
};


/*
 * Create a function that generates processes when
 * MainConsole calls scheduler-test
 */
void SchedulerManager::generateProcesses()
{

}

