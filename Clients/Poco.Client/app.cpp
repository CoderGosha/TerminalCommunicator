#include <stdio.h>
#include "src/worker.h"
#include <chrono>
#include <thread>
#include "src/timeout.h"

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
