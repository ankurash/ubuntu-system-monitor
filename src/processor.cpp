#include "processor.h"
// TODO: Return the aggregate CPU utilization
#include <vector>
#include <string>
using std::vector;
using std::string;

float Processor::Utilization() { 
    vector<string> cpu_utils = LinuxParser::CpuUtilization();
    return 50; 
}