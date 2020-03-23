#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stol;
using std::stof;
using std::stoi;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, temp, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> temp >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string temp, line;
  float memTotal, memFree, memAvailable, buffers, cached;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> temp >> memTotal;
    std::getline(stream, line);
    linestream = std::istringstream(line);
    linestream >> temp >> memFree;
    std::getline(stream, line);
    linestream = std::istringstream(line);
    linestream >> temp >> memAvailable;
    std::getline(stream, line);
    linestream = std::istringstream(line);
    linestream >> temp >> buffers;
    std::getline(stream, line);
    linestream = std::istringstream(line);
    linestream >> temp >> cached;
  }
  return (memTotal-memFree-buffers-cached)/memTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime_secs;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open())
  {
    stream>>uptime_secs;
  }
  return uptime_secs;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  long val = 0;
  vector<string> cpuUtilization = LinuxParser::CpuUtilization();
  for(int i = kUser_; i <= kSteal_; i++) {
    val += stol(cpuUtilization[i]);
  }
  return val;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line, temp;
  long utime, stime, cutime, cstime;
  std::ifstream filestream(kProcDirectory + std::to_string(pid)+ kStatFilename);
  if(getline(filestream, line))
  {
    std::istringstream linestream(line);
    for(int i=0; i<13; i++) linestream>>temp;
    linestream>>utime>>stime>>cutime>>cstime;
  }
  return utime+stime+cutime+cstime; //consider child processes as well
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  return (LinuxParser::Jiffies() - LinuxParser::IdleJiffies());
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  long val = 0;
  vector<string> cpuUtilization = LinuxParser::CpuUtilization();
  for(int i = kIdle_; i <= kIOwait_; i++) {
    val += stol(cpuUtilization[i]);
  }
  return val;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, temp;
  vector<string> cpu_util;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    if(getline(filestream, line)) //only reading the first line
    {
      if(line.find("cpu") != std::string::npos)
      {
        std::istringstream linestream(line);
        while(linestream>>temp)
        {
          if(temp != "cpu")
          {
            cpu_util.push_back(temp);
          }
        }
      }
    }
  }
  return cpu_util; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, temp;
  long pids;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    while(getline(filestream, line))
    {
      if(line.find("processes") != std::string::npos)
      {
        std::istringstream linestream(line);
        linestream >> temp >> pids;
        return pids;
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string temp, line;
  char pstate;
  int runningProcessesCount = 0;
  for(int pid: LinuxParser::Pids())
  {
    std::ifstream filestream(kProcDirectory + std::to_string(pid)+ kStatFilename);
    if(getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream>>temp>>temp>>pstate;
      if(pstate=='R' || pstate=='S')  //consider running or suspended processes as running
        runningProcessesCount++;
    }
  }
  return runningProcessesCount;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line); //However, some processes don't have this file
    return line;
  }
  return string();
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  string line, temp, unit;
  long mem=0;
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      if(line.find("VmSize:") != std::string::npos)
      {
        std::istringstream linestream(line);
        linestream >> temp >> mem >> unit;
        mem = mem/1024; //convert to Mb
        return to_string(mem);
      }
    }
  }
  return "0";
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  string line, temp, uid;
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      if(line.find("Uid: ") != std::string::npos)
      {
        std::istringstream linestream(line);
        linestream>>temp>>uid;
        return uid;
      }
    }
  }
  return string(); 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = LinuxParser::Uid(pid);
  string user, line;
  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      if(line.find(":x:"+uid) != std::string::npos)
      {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        linestream>>user;
        return user;
      }
    }
  }
  return string(); 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line, temp;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for(int i=0; i<=21; i++)
    {
      linestream >> temp;
    }
    return stol(temp)/sysconf(_SC_CLK_TCK);
  }
  return 0;
}