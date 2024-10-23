#pragma once
#include <mutex>
#include <unordered_map>
#include <vector>

#include "AScheduler.h"
#include "CPUWorker.h"
#include "Process.h"
#include "SchedulerWorker.h"

class FCFSScheduler : public AScheduler {
public:
  FCFSScheduler(int num_cpu);
  ~FCFSScheduler() = default;
  // void addProcess(std::shared_ptr<Process> process);

  void init() override;
  void run() override;
  void execute() override;

  void addProcess(std::shared_ptr<Process> process) override;
  std::shared_ptr<Process> findProcess(String process_name) override;
  std::unordered_map<String, std::shared_ptr<Process>>& getProcesses() override;
  String returnProcessInfo() const override;

private:
  int num_cpu;
  std::vector<CPUWorker> cpu_workers;
  int delay_per_exec = 0;
  std::unordered_map<String, std::shared_ptr<Process>> processes;
  std::vector<std::shared_ptr<Process>> ready_queue;
  std::vector<std::shared_ptr<Process>> finished_processes;
  std::mutex mtx;

  friend class GlobalScheduler;
};
