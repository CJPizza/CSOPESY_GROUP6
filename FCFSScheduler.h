#pragma once
#include "AScheduler.h"

class FCFSScheduler : public AScheduler {
public:
  FCFSScheduler();
  ~FCFSScheduler();

  void init() override;

private:
  
};
