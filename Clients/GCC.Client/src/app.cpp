#include<stdio.h>
#include "worker.h"
#include <unistd.h>
#include <chrono>
#include <thread>
#include "timeout.h"

int main()
{
    printf("\nStart ldnode \n\n");
    worker w = worker();

    while (true)
    {
        try
        {
            w.worker_do();
        }
        catch(const std::exception& e)
        {
            fprintf(stderr, "worker failed: %s\n", e.what());
            timeout::increment_error();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout::get_timeout()));
    }
    
    return 0;
}
