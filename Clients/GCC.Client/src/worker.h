//#include "clients/client_curl.h"
#include "clients/client_socket.h"
#include "json-parser/json.c"
#include "providers/exec_provider.h"
#include "providers/get_provider.h"
#include "log.h"

class worker
{
private:
    /* data */
    //client_curl clnt;
    client_socket clnt;
    ExecProvider exec_prvd;
    GetProvider get_proider;

    int eval_message(std::string);
    int process_message(json_value* value, std::string& id, std::string& response);
    int send_result_messge(std::string id, std::string response, int status);
public:
    worker(/* args */);
    ~worker();
    int worker_do();
};

worker::worker(/* args */)
{
    clnt = client_socket();
    exec_prvd = ExecProvider();
    get_proider = GetProvider();
}

worker::~worker()
{
}

int worker::worker_do(){
    printf("\nPing processing \n\n");
    clnt.ping();
    printf("\nPing finish \n\n");

    auto response = clnt.get_events();
    eval_message(response);

    return 0;
}

int worker::eval_message(std::string request){
    
    json_char* json;
    json_value* value;
    std::string id;
    std::string response;
    int status = 0;

    value = json_parse(request.c_str(), strlen(request.c_str()));
    if (value == NULL) {
        LogPrint("Unable to parse data");
        return -1;
    }
    int length, x;
    switch (value->type)
    {
        case json_array:
            length = value->u.array.length;
            for (x = 0; x < length; x++) {
                try {
                    status = process_message(value->u.array.values[x], id, response);
                    LogPrint("Response message id:" + id);
                }
                catch (const std::exception& e)
                {
                    status = 0;
                    response = e.what();
                }
                if (id.length() > 1)
                    send_result_messge(id, response, status);
            }
            break;
    
        default:
            break;
    }
    response = "";
    return 0;
}

int worker::process_message(json_value* value, std::string& id, std::string& response){
    int length, x;
    int status = 0;
    std::string request;
    int event_type;
    std::string id_name = "id";
    std::string request_name = "request";
    std::string event_type_name = "event_type";
    std::string key;

    if (value == NULL) {
        return -1;
    }
    length = value->u.object.length;
    for (x = 0; x < length; x++) {
        switch (value->type)
        {
            case json_object:
                key = std::string(value->u.object.values[x].name);
                if (key == id_name)
                    id = value->u.object.values[x].value->u.string.ptr;
                if (key == request_name)
                    request = value->u.object.values[x].value->u.string.ptr;
                if (key == event_type_name)
                    event_type = (long)value->u.object.values[x].value->u.integer;
                break;
            default:
                break;
        }
    }
    LogPrint("Message new:" + id);
    
    switch (event_type)
    {
    case 0:
        // exec
        {
            status = exec_prvd.exec(id, request, response);
            break;
        }
    case 1:
        {
            status = get_proider.exec(id, request, response);
            break;
        }
    default:
        {
            status = 0;
            response = "unknown event type";
            break;
        }

    }
    
    return status;
}

int worker::send_result_messge(std::string id, std::string response, int status){
    return clnt.post_event(id, response, status);
}