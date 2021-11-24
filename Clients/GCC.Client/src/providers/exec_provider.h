#include<stdio.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

class exec_provider
{
private:
    /* data */
public:
    exec_provider(/* args */) {};
    ~exec_provider() {};
    int exec(std::string& id, std::string request, std::string& response);
};

 int exec_provider::exec(std::string& id, std::string request, std::string& response){
    int status = 1;
    time_t time_now = time(NULL);
    time_t time_fliex = time_now + 60 * 1;

    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(request.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
       result += buffer.data();
       time_now = time(NULL);
       if (time_fliex < time_now)
          break;
    }

    response = result;

    if (time_fliex < time_now){
            response += "\n stoped timeout \n";
    }    
    return status;
 }