#include<stdio.h>
#include "client.h"
#include "timeout.h"
#include <unistd.h>
#include <chrono>
#include <thread>

int main()
{
    printf("\nStart ldnode \n\n");
    timeout tout = timeout();

    while (true)
    {
        try
        {
            printf("\nPing processing \n\n");
            ping();
            printf("\nPing finish \n\n");
        }
        catch(const std::exception& e)
        {
            //std::cerr << e.what() << '\n';
            tout.increment_error();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(tout.get_timeout()));
    }
    
    return 0;
}
