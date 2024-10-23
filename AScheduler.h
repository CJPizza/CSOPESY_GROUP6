#pragma once

#include "IETThread.h"
#include "Process.h"
#include <unordered_map>

static const String FCFS_SCHEDULER_NAME = "FCFSScheduler";
static const String ROUND_ROBIN_NAME = "RRScheduler";

class AScheduler : public IETThread {
public:
  enum SchedulingAlgorithm
  {
    FCFS,
    ROUND_ROBIN
  };

  AScheduler(SchedulingAlgorithm scheduling_algo, String process_name);
  ~AScheduler();


  void addProcess(std::shared_ptr<Process> process);
  std::shared_ptr<Process> findProcess(String process_name);
  void run() override;
  void stop();

  virtual void init() = 0;
  virtual void execute() = 0;

private:
  std::unordered_map<String, Process> processes;

  friend class GlobalScheduler;
};
