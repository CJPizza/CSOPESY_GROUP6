#pragma once
#include <memory>
#include <unordered_map>

#include "CPUWorker.h"
#include "IETThread.h"
#include "Process.h"

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

  virtual void addProcess(std::shared_ptr<Process> process) = 0;
  virtual std::shared_ptr<Process> findProcess(String process_name) = 0;
  virtual std::unordered_map<String, std::shared_ptr<Process>>& getProcesses() = 0;
  virtual String returnProcessInfo() const = 0; // returns process info
  virtual void startSchedTest() = 0; // starts scheduler-test
  virtual void stopSchedTest() = 0;
  void run() override;
  void stop();

  virtual void init() = 0;
  virtual void execute() = 0;

protected:
  // all the processes in the scheduler

};
