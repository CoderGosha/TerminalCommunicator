#include "client.h"

class worker
{
private:
    /* data */
    client clnt;
public:
    worker(/* args */);
    ~worker();
    int worker_do();
};

worker::worker(/* args */)
{
    clnt = client();
}

worker::~worker()
{
}

int worker::worker_do(){
    printf("\nPing processing \n\n");
    clnt.ping();
    printf("\nPing finish \n\n");

    auto response = clnt.get_events();
    printf(response.c_str());
    //fprintf(stdout, "\nEvent count: %s\n", response);
    return 0;
}

