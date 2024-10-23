#pragma once

#include "CPUWorker.h"
#include "IETThread.h"
#include "Process.h"
#include <unordered_map>

static const String FCFS_SCHEDULER_NAME = "FCFSScheduler";
static const String ROUND_ROBIN_NAME = "RRScheduler";

class AScheduler : public IETThread {
public:
  // I don't know what to do with this
  enum SchedulingAlgorithm
  {
    FCFS,
    ROUND_ROBIN
  };

  AScheduler(SchedulingAlgorithm scheduling_algo);
  ~AScheduler() = default;


  void addProcess(std::shared_ptr<Process> process);
  std::shared_ptr<Process> findProcess(String process_name);
  void run() override;
  void stop();

  virtual void init() = 0;
  virtual void execute() = 0;

private:
  // all the processes in the scheduler
  std::unordered_map<String, std::shared_ptr<Process>> processes;
  std::vector<CPUWorker> cpu_workers;

  friend class GlobalScheduler;
};
