#include <string>
#include "log.h"

#ifndef TIMEOUT_H
#define TIMEOUT_H

class timeout
{
private:
    static int const timeout_long = 30;
    static int const timeout_very_long = 30 * 60;

public:
    static int const timeout_default = 10;
    static int timeout_current;
    static int error_count;
    static time_t error_time;

    static int get_timeout(){
        return 1000 * timeout_current;
    };
    static void increment_error()
    {
        time_t time_now = time(NULL);
        time_t time_fliex = error_time + 60 * 60 * 3;

        if (time_fliex < time_now){
            error_count = 0;
            timeout_current = timeout_default;
        }

       
        LogPrint("increment_error: " + std::to_string(error_count));

        struct tm *tm = localtime(&error_time);
        error_count += 1;

        if (error_count > 1000){
            LogPrint("Close app. Error count: " + std::to_string(error_count));
            exit(1);
        }

        if (error_count > 500){
            timeout_current = timeout_very_long;
            return;
        }

        if (error_count > 50){
            timeout_current = timeout_long;
            return;
        }
    };

    timeout(/* args */) {};
    ~timeout() {};
};

int timeout::error_count = 0;
time_t timeout::error_time = time(NULL);
int timeout::timeout_current = timeout::timeout_default;

#endif

