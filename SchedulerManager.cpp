#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <random>

#include "SchedulerManager.h"
#include "Process.h"

bool isGenerating;

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
    // The behavior is as follows: Every X CPU cycles, a new process is generated and put into the ready queue for your CPU scheduler. 
    // This frequency can be set in the “config.txt.” As long as CPU cores are available, 
    // each process can be executed and be accessible via the “screen” command.
    String pname;
    uint32_t proclines;
    int procnumname = 0;
    std::stringstream procname;
    isGenerating = true;

    while(isGenerating){
        if( //cpucycle 
        % batch_process_freq == 0){ //activates for every batch_freq
        //increment string name
        procnumname++;
        procname << "proc" << std::setw(2) << std::setfill('0') << procnumname;
        
        //random proclines within range
        std::random_device rd;
        std::mt19937 gen(rd());
        
        std::uniform_int_distribution<> distrib(min_ins, max_ins);
        
        proclines = distrib(gen);
        
        //create new process
        std::shared_ptr<Process> newProcess = std::make_shared<Process>(procname, proclines);
        //push to ready queue or smthn here vvv

        //add threading?
        }
    }
}

void SchedulerManager::stopGenerateProcesses(){
    isGenerating = false;
    //hypothetically this should stop the loop lol
}

int SchedulerManager::getMinIns(){
    return this->min_ins;
}

int SchedulerManager::getMaxIns(){
    return this->max_ins;
}