#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    // int USER_HZ = 100;
    long totalJiffiesStart=0, activeJiffiesStart=0, totalJiffiesEnd=0, activeJiffiesEnd=0;
};

#endif