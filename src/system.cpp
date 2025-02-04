#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
	//Processor cpu;
	return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
	vector<int> pids = LinuxParser::Pids();
	//remove terminated processes
	for(int i=0; i<int(processes_.size()); i++)
	{
		if(std::find(pids.begin(), pids.end(), processes_[i].Pid()) == pids.end())
		{
			processes_.erase(processes_.begin()+i);
			i--;
		}
	}

	//Add new processes without reinitializing old processes
	for(int pid: pids)
	{
		bool processExists= false;
		for(int i=0; i<int(processes_.size()); i++)
		{
			if(processes_[i].Pid() == pid)
			{
				processExists=true;
				break;
			}
		}
		if(!processExists)
			processes_.push_back(Process(pid));
	}
	std::sort(processes_.begin(), processes_.end());
	return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }