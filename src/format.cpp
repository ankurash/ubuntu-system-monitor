#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    string time[3];
    time[0] = std::to_string(seconds/3600);
    time[1] = std::to_string((seconds%3600)/60);
    time[2] = std::to_string(seconds%60);
    for(int i=0; i<3; i++)
    {
        if(time[i].length()<2)
            time[i] = "0" + time[i];
    }
    return time[0]+":"+time[1]+":"+time[2];
}