#pragma once

#include "IETThread.h"
#include "Process.h"
#include <mutex>

class CPUWorker : public IETThread {
public:
  CPUWorker();
  ~CPUWorker() = default;

  void run() override;
  void execute();

  void assignProcess(std::shared_ptr<Process> process);

private:
  bool executing = false;
  std::shared_ptr<Process> process;
  inline static int new_id = 0;
  int uid;

  friend class FCFSScheduler;
  // friend class RRScheduler
};
