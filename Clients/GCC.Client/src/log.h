#include <string>
#include <iostream>

#ifndef LOG_H
#define LOG_H

inline std::string getCurrentDateTime(std::string s ){
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    if(s=="now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if(s=="date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return std::string(buf);
};

void LogPrint(std::string message){
    #ifdef DEBUG
    
    std::string filePath = "log_"+getCurrentDateTime("date")+".txt";
    std::string now = getCurrentDateTime("now");
    std::string msg = now + "\t" + message +"\n";
    printf(msg.c_str());
    
    std::ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app );
    ofs << now << '\t' << message << '\n';
    ofs.close();
    
    #endif
}

void LogPrint(std::string message, const std::exception& e){
    std::string msg = message + e.what();
    LogPrint(message);
}

#endif