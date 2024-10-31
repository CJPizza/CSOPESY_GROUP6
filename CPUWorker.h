#pragma once

#include "IETThread.h"
#include "Process.h"
#include <memory>
#include <mutex>
#include <vector>

class CPUWorker : public IETThread {
public:
  CPUWorker();
  ~CPUWorker() = default;

  void run() override;
  void execute();
  
  int getCoreID() const;

  void assignProcess(std::shared_ptr<Process> process);
  std::shared_ptr<Process> getCurrentProcess() const;

  bool getExecuting() const;
  void setExecuting(bool executing);

  void clearProcess();
  void setQuantumDec(int quant_rem);
  int getQuantumDec() const;
  void setRR();

private:
  bool executing = false;
  std::shared_ptr<Process> process;

  inline static int new_id = 0;
  int uid;

  int quant_cycle_rem; // remaining line execution before changing to another process
  bool isRR = false;       // if scheduler is ROUND_ROBIN 
  // friend class RRScheduler
};
