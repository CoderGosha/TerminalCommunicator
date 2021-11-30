#include <string>

#ifndef LOG_H
#define LOG_H

bool logEnable = true;

void LogPrint(std::string message){
    if (!logEnable)
        return;
        
    auto msg = message + "\n"; 
    printf(msg.c_str());
}

#endif