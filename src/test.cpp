// #ifndef SYSTEM_PARSER_H
// #define SYSTEM_PARSER_H

// #include <fstream>
// #include <dirent.h>
// #include <unistd.h>
// #include <string>
// #include <vector>
// #include <regex>
// #include<iostream>

// namespace LinuxParser {
// // Paths
// const std::string kProcDirectory{"/proc/"};
// const std::string kCmdlineFilename{"/cmdline"};
// const std::string kCpuinfoFilename{"/cpuinfo"};
// const std::string kStatusFilename{"/status"};
// const std::string kStatFilename{"/stat"};
// const std::string kUptimeFilename{"/uptime"};
// const std::string kMeminfoFilename{"/meminfo"};
// const std::string kVersionFilename{"/version"};
// const std::string kOSPath{"/etc/os-release"};
// const std::string kPasswordPath{"/etc/passwd"};
// const std::string kTimerList("timer_list");

// // System
// float MemoryUtilization();
// long UpTime();
// std::vector<int> Pids();
// int TotalProcesses();
// int RunningProcesses();
// std::string OperatingSystem();
// std::string Kernel();

// // CPU
// enum CPUStates {
//   kUser_ = 0,
//   kNice_,
//   kSystem_,
//   kIdle_,
//   kIOwait_,
//   kIRQ_,
//   kSoftIRQ_,
//   kSteal_,
//   kGuest_,
//   kGuestNice_
// };
// std::vector<std::string> CpuUtilization();
// long Jiffies();
// long ActiveJiffies();
// long ActiveJiffies(int pid);
// long IdleJiffies();

// // Processes
// std::string Command(int pid);
// std::string Ram(int pid);
// std::string Uid(int pid);
// std::string User(int pid);
// long int UpTime(int pid);
// };  // namespace LinuxParser

// #endif

// #include <dirent.h>
// #include <unistd.h>
// #include <string>
// #include <vector>

// using std::stof;
// using std::string;
// using std::to_string;
// using std::vector;

// // DONE: An example of how to read data from the filesystem
// string LinuxParser::OperatingSystem() {
//   string line;
//   string key;
//   string value;
//   std::ifstream filestream(kOSPath);
//   if (filestream.is_open()) {
//     while (std::getline(filestream, line)) {
//       std::replace(line.begin(), line.end(), ' ', '_');
//       std::replace(line.begin(), line.end(), '=', ' ');
//       std::replace(line.begin(), line.end(), '"', ' ');
//       std::istringstream linestream(line);
//       while (linestream >> key >> value) {
//         if (key == "PRETTY_NAME") {
//           std::replace(value.begin(), value.end(), '_', ' ');
//           return value;
//         }
//       }
//     }
//   }
//   return value;
// }

// // DONE: An example of how to read data from the filesystem
// string LinuxParser::Kernel() {
//   string os, kernel, temp;
//   string line;
//   std::ifstream stream(kProcDirectory + kVersionFilename);
//   if (stream.is_open()) {
//     std::getline(stream, line);
//     std::istringstream linestream(line);
//     linestream >> os >> temp>>kernel;
//   }
//   return kernel;
// }

// // BONUS: Update this to use std::filesystem
// vector<int> LinuxParser::Pids() {
//   vector<int> pids;
//   DIR* directory = opendir(kProcDirectory.c_str());
//   struct dirent* file;
//   while ((file = readdir(directory)) != nullptr) {
//     // Is this a directory?
//     if (file->d_type == DT_DIR) {
//       // Is every character of the name a digit?
//       string filename(file->d_name);
//       if (std::all_of(filename.begin(), filename.end(), isdigit)) {
//         int pid = stoi(filename);
//         pids.push_back(pid);
//       }
//     }
//   }
//   closedir(directory);
//   return pids;
// }

// // TODO: Read and return the system memory utilization
// float LinuxParser::MemoryUtilization() { 
//   string temp, line;
//   float memtotal, memfree;
//   std::ifstream stream(kProcDirectory + kMeminfoFilename);
//   if (stream.is_open()) {
//     std::getline(stream, line);
//     std::istringstream linestream(line);
//     linestream >> temp >> memtotal;
//     std::getline(stream, line);
//     linestream = std::istringstream(line);
//     linestream >> temp >> memfree;
//   }
//   return 100*(memtotal-memfree)/memtotal;
// }

// // TODO: Read and return the system uptime
// long LinuxParser::UpTime() { 
//   long uptime_secs;
//   std::ifstream stream(kProcDirectory + kUptimeFilename);
//   if(stream.is_open())
//   {
//     stream>>uptime_secs;
//   }
//   return uptime_secs;
// }

// // TODO: Read and return the number of jiffies for the system
// long LinuxParser::Jiffies() { 
//   std::ifstream filestream(kProcDirectory + kTimerList);
//   string line, temp;
//   long jiffies;
//   if (filestream.is_open()) {
//     while (std::getline(filestream, line)) {
//       if(line.find("jiffies: ") != std::string::npos)
//       {
//         std::istringstream linestream(line);
//         linestream >> temp >> jiffies;
//         return jiffies;
//       }
//     }
//   }
//   return 0;
// }

// // TODO: Read and return the number of active jiffies for a PID
// // REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 

//   return 0;
// }

// // TODO: Read and return the number of active jiffies for the system
// long LinuxParser::ActiveJiffies() { return 0; }

// // TODO: Read and return the number of idle jiffies for the system
// long LinuxParser::IdleJiffies() { return 0; }

// // TODO: Read and return CPU utilization
// vector<string> LinuxParser::CpuUtilization() { return {}; }

// // TODO: Read and return the total number of processes
// int LinuxParser::TotalProcesses() { return LinuxParser::Pids().size(); }

// // TODO: Read and return the number of running processes
// int LinuxParser::RunningProcesses() { return 0; }

// // TODO: Read and return the command associated with a process
// // REMOVE: [[maybe_unused]] once you define the function
// string LinuxParser::Command(int pid) {
//   string line;
//   std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
//   if(filestream.is_open())
//   {
//     std::getline(filestream, line);
//     return line;
//   }
//   return string();
// }

// // TODO: Read and return the memory used by a process
// // REMOVE: [[maybe_unused]] once you define the function
// string LinuxParser::Ram(int pid) {
//   std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
//   string line, temp, unit;
//   long mem;
//   if(filestream.is_open())
//   {
//     while(std::getline(filestream, line))
//     {
//       if(line.find("VmSize: ") != std::string::npos)
//       {
//         std::istringstream linestream(line);
//         linestream >> temp >> mem >> unit;
//         mem = mem/1024;
//         return to_string(mem);
//       }
//     }
//   }
//   return string();
// }

// // TODO: Read and return the user ID associated with a process
// // REMOVE: [[maybe_unused]] once you define the function
// string LinuxParser::Uid(int pid) { 
//   std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
//   string line, temp, uid;
//   if(filestream.is_open())
//   {
//     while(std::getline(filestream, line))
//     {
//       if(line.find("Uid: ") != std::string::npos)
//       {
//         std::istringstream linestream(line);
//         linestream>>temp>>uid;
//         return uid;
//       }
//     }
//   }
//   return string(); 
// }

// // TODO: Read and return the user associated with a process
// // REMOVE: [[maybe_unused]] once you define the function
// string LinuxParser::User(int pid) { 
//   string uid = LinuxParser::Uid(pid);
//   string user, line;
//   std::ifstream filestream(kPasswordPath);
//   if(filestream.is_open())
//   {
//     while(std::getline(filestream, line))
//     {
//       if(line.find(":x:"+uid))
//       {
//         std::replace(line.begin(), line.end(), ':', ' ');
//         std::istringstream linestream(line);
//         linestream>>user;
//         return user;
//       }
//     }
//   }
//   return string(); 
// }

// // TODO: Read and return the uptime of a process
// // REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }


// int main()
// {
//   std::cout<<LinuxParser::OperatingSystem()<<","<<LinuxParser::Kernel()<<","<<LinuxParser::MemoryUtilization()<<","<<LinuxParser::UpTime()<<","<<LinuxParser::Jiffies()<<","<<LinuxParser::TotalProcesses();
//     return 0;
// }

