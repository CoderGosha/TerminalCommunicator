#include "client.h"
#include "json-parser/json.c"

class worker
{
private:
    /* data */
    client clnt;
   
    int eval_message(const char *);
    int process_message(json_value* value, std::string& id, std::string& response);
    int send_result_messge(std::string id, std::string response, int status);
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
    eval_message(response.c_str());

    return 0;
}

int worker::eval_message(const char * request){
    printf("%.*s\n", request);
    json_char* json;
    json_value* value;
    std::string id;
    std::string response;
    int status = 0;

    value = json_parse(request, strlen(request));
    if (value == NULL) {
                fprintf(stderr, "Unable to parse data\n");
                return -1;
    }
    int length, x;
    switch (value->type)
    {
        case json_array:
            length = value->u.array.length;
            for (x = 0; x < length; x++) {
                status = process_message(value->u.array.values[x], id, response);
                printf("Response message id: %s\n", id.c_str());
                send_result_messge(id, response, status);
            }
            break;
    
        default:
            break;
    }
    return 0;
}

int worker::process_message(json_value* value, std::string& id, std::string& response){
    int length, x;
    
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
    printf("Message new: %s\n", id.c_str());
    response = "ok";
    return 1;
}

int worker::send_result_messge(std::string id, std::string response, int status){
    return clnt.post_event(id, response, status);
}