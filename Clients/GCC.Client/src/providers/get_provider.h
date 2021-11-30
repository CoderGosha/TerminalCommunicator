
#include "../clients/httplib.h"

class GetProvider
{
private:
    /* data */
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
    httplib::Client cli(request);
    cli.set_default_headers({
        { "User-Agent", user_agetn },
        });
    cli.set_follow_location(true);

    auto res = cli.Get("");
    if (res->status == 200);
        status = 1;
    
    response = res->body;
    return status;
}