#include<stdio.h>
#include "worker.h"
#include "timeout.h"
#include <unistd.h>
#include <chrono>
#include <thread>

int main()
{
    printf("\nStart ldnode \n\n");
    timeout tout = timeout();
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
            tout.increment_error();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(tout.get_timeout()));
    }
    
    return 0;
}
