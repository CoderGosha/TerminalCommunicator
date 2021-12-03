#define CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_READ_TIMEOUT_SECOND 20
#define DEBUG
#include "clients/httplib.h"
#include <stdio.h>
#include "worker.h"
#include <unistd.h>
#include <chrono>
#include <thread>
#include "timeout.h"

int main()
{
    LogPrint("Start ldnode");
    
    worker w = worker();

    while (true)
    {
        try
        {
            w.worker_do();
        }
        catch(const std::exception& e)
        {
            LogPrint("worker failed: ", e);
            fprintf(stderr, "worker failed: %s\n", e.what());
            timeout::increment_error();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout::get_timeout()));
    }
    
    return 0;
}
