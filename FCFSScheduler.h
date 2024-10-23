#pragma once
#include <memory>
#include <vector>

#include "AScheduler.h"
#include "CPUWorker.h"
#include "SchedulerWorker.h"

class FCFSScheduler : public AScheduler {
public:
  FCFSScheduler(int num_cpu);
  ~FCFSScheduler() = default;

  void addProcess(std::shared_ptr<Process> process);

  void init() override;
  void run() override;
  void execute() override;

private:
  int num_cpu;
  std::vector<CPUWorker> cpu_workers;
  std::vector<String> processes_order; // contains keys for table in GlobalScheduler order to when the processes were added
  std::vector<std::shared_ptr<Process>> process_queues; // process queue

  friend class GlobalScheduler;
};
