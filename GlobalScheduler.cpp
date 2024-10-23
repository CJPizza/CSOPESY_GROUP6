#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>

#include "GlobalScheduler.h"
#include "AScheduler.h"

GlobalScheduler* GlobalScheduler::sharedInstance = nullptr;

GlobalScheduler* GlobalScheduler::getInstance() 
{
    if (sharedInstance == nullptr) 
    {
        sharedInstance = new GlobalScheduler();
    }
    return sharedInstance;
}

void GlobalScheduler::initialize()
{
    if (sharedInstance == nullptr) {
        sharedInstance = new GlobalScheduler();
    } else {
        std::cerr << "GlobalScheduler already initialized." << std::endl;
    }
}

void GlobalScheduler::destroy()
{
    delete sharedInstance;
}

/*
 * Create a function that generates processes when
 * MainConsole calls scheduler-test
 */
void GlobalScheduler::generateProcesses()
{

}

void GlobalScheduler::addProcess(std::shared_ptr<Process> newProcess)
{
  // add the process to the appropriate scheduler

}

std::shared_ptr<Process> GlobalScheduler::findProcess(String process_name) const
{

}

void GlobalScheduler::loadConfig()
{
  config_kvs map_scheduler = {
    // maps string to corresponding int as representation when parsing config.txt
    {"fcfs", 0},
    {"rr", 1},
  };

  // https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c
  std::ifstream is_file;
  is_file.open("config.txt");

  // if `config.txt` does not exists
  if(!is_file.good())
  {
    std::cout << "config.txt does not exists";
    return;
  }

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

  if(config["scheduler"] == 0)
  {
    this->scheduler = new FCFSScheduler();
  } else {
    // scheduler = new RRScheduler
  }

  // If you want to check what the contents of config are
  // for (const std::pair<const String, int>& n : config){
  //     std::cout << n.first << ": " << n.second << "\n";
  // }

  is_file.close();
}

void GlobalScheduler::tick()
{
  this->scheduler->execute();
}
