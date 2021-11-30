#include "../clients/httplib.h"

class GetProvider
{
private:
    std::string SpitUrl(std::string url, std::string& params);
public:
    GetProvider(/* args */);
    ~GetProvider();
    int exec(std::string& id, std::string request, std::string& response);
};

GetProvider::GetProvider(/* args */)
{
}

GetProvider::~GetProvider()
{
}

int GetProvider::exec(std::string& id, std::string request, std::string& response){
    int status = 0;
    auto user_agetn = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:62.0) Gecko/20100101 Firefox/62.0";
    std::string params;
    std::string base_url = SpitUrl(request, params);

    httplib::Client cli(base_url);
    cli.set_default_headers({
        { "User-Agent", user_agetn },
        });
    cli.set_follow_location(true);

    auto res = cli.Get(params.c_str());
    if (res->status == 200){
        status = 1;
    }
    response = res->body;
    return status;
}

std::string GetProvider::SpitUrl(std::string url, std::string& params){
    params = "/";
    std::size_t separator = url.find("://");  

    std::size_t split_pos = url.find_first_of("/", separator + 3);
    
    params = url.substr(split_pos);
    return url.substr(0, split_pos);
}