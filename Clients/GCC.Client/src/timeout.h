class timeout
{
private:
    int timeout_default = 10;
    int timeout_long = 30;
    int timeout_very_long = 30 * 60;
    int timeout_current = 1;

    int error_count = 0;
    time_t error_time = time(NULL);

public:
    int get_timeout(){
        return 1000 * timeout_current;
    }

    void increment_error(){
        time_t time_now = time(NULL);
        time_t time_fliex = error_time * 60 * 60 * 3;

        if (time_fliex < time_now){
            error_count = 0;
            timeout_current = timeout_default;
        }

        struct tm *tm = localtime(&error_time);
        error_count += 1;

        if (error_count > 1000){
            printf("\nClose app. Error count 1000\n\n");
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
    }

    timeout(/* args */);
    ~timeout();
};

timeout::timeout(/* args */)
{
    timeout_current = timeout_default;
}

timeout::~timeout()
{
}

