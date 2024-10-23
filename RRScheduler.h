#pragma once

#include <deque>
#include <mutex>
#include <vector>

#include "AScheduler.h"

class RRScheduler : public AScheduler
{

  void init() override;
  void run() override;
  void execute() override;
};
