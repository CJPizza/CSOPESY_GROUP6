#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <sys/types.h>

#include "GlobalScheduler.h"
#include "AScheduler.h"
#include "ConsoleDriver.h"
#include "FCFSScheduler.h"

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

// std::shared_ptr<Process> GlobalScheduler::createUniqueProcess()
// {
//
// }

/*
 * Create a function that generates processes when
 * MainConsole calls scheduler-test
 */
void GlobalScheduler::generateProcesses()
{

}

void GlobalScheduler::addProcess(std::shared_ptr<Process> new_process)
{
  // if the process already exists
  if (findProcess(new_process->getProcessName()) != nullptr)
  {
    return;
  }
  this->scheduler->addProcess(new_process);
  ConsoleDriver::getInstance()->registerScreen(std::make_shared<BaseScreen>(new_process, new_process->getProcessName()));
}

std::shared_ptr<Process> GlobalScheduler::findProcess(String process_name) 
{
  return processes[process_name];
}

void GlobalScheduler::loadConfig()
{
  config_kvs configs;

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
          configs[key] = map_scheduler[value];
        } else {
          configs[key] = std::stoi(value);
        }
        // std::cout << key << ": " << value << "\n";
      }
    }
  }

  // save configs into variable
  this->num_cpu = configs["num_cpu"];
  this->quantum_cycles = configs["quantum_cycles"];
  this->batch_process_freq = configs["batch_process_freq"];
  this->max_ins = configs["max_ins"];
  this->min_ins = configs["min_ins"];
  this->delay_per_exec = configs["delay_per_exec"];

  if(configs["scheduler"] == 0)
  {
    this->scheduler = new FCFSScheduler(num_cpu);
  } else {
    // if scheduler is ROUND_ROBIN add here
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

String GlobalScheduler::strProcessesInfo() const
{
  std::stringstream str_stream;
  str_stream << "Running Processes: \n";

  return str_stream.str();
}

SchedulerWorker GlobalScheduler::getSchedWorker()
{
  return this->sched_worker;
}

void GlobalScheduler::startScheduler() const
{
  this->scheduler->init();
  this->scheduler->start();
}
