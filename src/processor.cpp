#include "processor.h"
#include "linux_parser.h"
#include <unistd.h>
// TODO: Return the aggregate CPU utilization
#include <vector>
#include <string>
using std::vector;
using std::string;

float Processor::Utilization() { 
  //vector<string> cpu_utils = LinuxParser::CpuUtilization();
  totalJiffiesStart = LinuxParser::Jiffies();
  activeJiffiesStart = LinuxParser::ActiveJiffies();
  
  usleep(100000); // microseconds --> 100 milliseconds
  
  totalJiffiesEnd = LinuxParser::Jiffies();
  activeJiffiesEnd = LinuxParser::ActiveJiffies();
  
  float totalDelta = totalJiffiesEnd - totalJiffiesStart;
  float activeDelta = activeJiffiesEnd - activeJiffiesStart;
  
  if (totalDelta == 0) {
    return 0.0;
  }
  
  return activeDelta / totalDelta;
}
