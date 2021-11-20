class timeout
{
private:
    int timeout_default = 10;
    int timeout_long = 30;
    int timeout_very_long = 30 * 60;
    int timeout_current = 1;
public:
    int get_timeout(){
        return 1000 * timeout_current;
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

