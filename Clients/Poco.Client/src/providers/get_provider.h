#include "../log.h"
#include <chrono>
#include <thread>

class GetProvider
{
private:
    std::string SpitUrl(std::string url, std::string& params);
public:
    GetProvider(/* args */);
    ~GetProvider();
    int exec(std::string& id, std::string request, std::string& response);
    int exec_get(std::string& id, std::string request, std::string& response);
};

GetProvider::GetProvider(/* args */)
{
}

GetProvider::~GetProvider()
{
}

int GetProvider::exec(std::string& id, std::string request, std::string& response){
    for (size_t i = 1; i <= 5; i++)
    {
        LogPrint("Try request: " + std::to_string(i));
        int status = exec_get(id, request, response);
        if (response.length() != 0)
            return status;
            
        std::this_thread::sleep_for(std::chrono::milliseconds((read_timeout_milliseconds())));
    }
    response = "Content is null";
    return 0;
}

int GetProvider::exec_get(std::string& id, std::string request, std::string& response){
    int status = 0;
    auto user_agetn = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:62.0) Gecko/20100101 Firefox/62.0";
    std::string params;
    std::string base_url = SpitUrl(request, params);

    LogPrint("Get request: " + request);

    // REVEW GET

    LogPrint("Response len:" + std::to_string(response.length()));
    if (response.length() == 0)
        return 0;

//    if (res != nullptr && response.length() != 0)
//        if (res->status == 200)
//            status = 1;

    // REVEW LogPrint("Response status: " + std::to_string(res->status));
    return status;
}

std::string GetProvider::SpitUrl(std::string url, std::string& params){
    params = "/";
    std::size_t separator = url.find("://");  

    std::size_t split_pos = url.find_first_of("/", separator + 3);
    
    params = url.substr(split_pos);
    return url.substr(0, split_pos);
}