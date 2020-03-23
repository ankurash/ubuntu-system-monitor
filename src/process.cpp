#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
// #include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::stol;

Process::Process(int pid)
{
    Process::pid_ = pid;
}

// TODO: Return this process's ID
int Process::Pid() { 
    return pid_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  float totalTime = float(LinuxParser::ActiveJiffies(pid_));
  float startTime = float(LinuxParser::UpTime(pid_));
  long upTime = LinuxParser::UpTime();
  float seconds = upTime - (startTime / sysconf(_SC_CLK_TCK));
  
  float currentSeconds = seconds-prevSeconds;
  float currentTotalTime = totalTime-prevTotalTime;
  if(seconds<prevSeconds)   //Probably is a new process
  {
    currentSeconds = seconds;
    currentTotalTime = totalTime;
  }
  currentCpuUtilization = (currentTotalTime / sysconf(_SC_CLK_TCK))/ currentSeconds;
  prevSeconds = seconds;
  prevTotalTime = totalTime;
  return currentCpuUtilization;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram() {
    return LinuxParser::Ram(pid_);
}

// TODO: Return the user (name) that generated this process
string Process::User() {
    return LinuxParser::User(pid_);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    // return stol(LinuxParser::Ram(pid_)) > stol(LinuxParser::Ram(a.pid_));    //sort by Ram utilization
     return currentCpuUtilization > a.currentCpuUtilization;    //sort by cpu utilization
}

