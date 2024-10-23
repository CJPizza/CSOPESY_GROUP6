#pragma once

#include "IETThread.h"
#include "Process.h"
#include <memory>
#include <mutex>

class CPUWorker : public IETThread {
public:
  CPUWorker();
  ~CPUWorker() = default;

  void run() override;
  void execute();
  
  int getCoreID() const;

  void assignProcess(std::shared_ptr<Process> process);
  std::shared_ptr<Process> getCurrentProcess() const;

  void setExecuting(bool executing);

private:
  bool executing = false;
  std::shared_ptr<Process> process;
  inline static int new_id = 0;
  int uid;

  // friend class RRScheduler
};
