#pragma once

#include "IETThread.h"
#include "Process.h"

class CPUWorker : public IETThread {
public:
  CPUWorker() = default;
  ~CPUWorker() = default;

  void run() override;
  void execute();

  void assignProcess(std::shared_ptr<Process> process);

private:
  bool executing;
  std::shared_ptr<Process> process;

  friend class FCFSScheduler;
  // friend class RRScheduler
};
