#include <string>
#include "../credential.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../timeout.h"
#include "../log.h"
#include <sstream>
#include <iomanip>
#include <iostream>

#include "httplib.h"

std::string escape_json(const std::string &s) {
    std::ostringstream o;
    for (auto c = s.cbegin(); c != s.cend(); c++) {
        if (*c == '"' || *c == '\\' || ('\x00' <= *c && *c <= '\x1f')) {
            o << "\\u"
              << std::hex << std::setw(4) << std::setfill('0') << (int)*c;
        } else {
            o << *c;
        }
    }
    return o.str();
}

class client_socket
{
private:
    /* data */
    httplib::Client get_client();
public:
    client_socket(/* args */);
    ~client_socket();
    int ping();
    std::string get_events();
    int post_event(std::string id, std::string response, int status);
};

client_socket::client_socket(/* args */)
{
}

client_socket::~client_socket()
{
}

httplib::Client client_socket::get_client(){
  std::string url = get_url();
  std::string token = get_token(); 

  httplib::Client cli(url);

  cli.set_bearer_token_auth(token.c_str());
  cli.set_default_headers({
  { "Authorization", token.c_str() },
  { "Content-Type", "application/json" },
  { "Accept", "application/json" },
  });
  cli.set_follow_location(true);
  return cli;
}

int client_socket::ping(){
  auto cli = get_client();

  std::string data = "{\"name\" : \"" + get_name() + "\", \"version\" : \"" + get_version() + "\" }";

  auto res = cli.Post("/api/ping/", data.c_str(), "application/json");
  if (res->status == 200){
      return 1;
  }
  timeout::increment_error();
  fprintf(stderr, "httplib) failed, code:%i, message: %s\n", res->status, res->body);
  return 0;
}

std::string client_socket::get_events(){
  LogPrint("Check events");
  std::string response = "[]";
  auto cli = get_client();
  auto url_event = "/api/event?name=" + get_name();
  auto res = cli.Get(url_event.c_str());
  if (res->status == 200)
    {
      LogPrint("Events: " + std::to_string(res->status)+ ", body:" + res->body);
      //response = res->body;
      return res->body;
    }
  timeout::increment_error();
  fprintf(stderr, "httplib) failed, code:%i, message: %s\n", res->status, res->body);
  return response;
}

int client_socket::post_event(std::string id, std::string response, int status){
  auto cli = get_client();

  std::string status_str = std::to_string(status);
  std::string response_escape = escape_json(response); 
  std::string data = "{\"id\" : \"" + id + "\", \"response\" : \"" + response_escape + "\" , \"success\" : " + status_str + "}";

  auto res = cli.Post("/api/event/", data.c_str(), "application/json");
  if (res->status == 200){
      return 1;
  }
  timeout::increment_error();
  fprintf(stderr, "httplib) failed, code:%i, message: %s\n", res->status, res->body);
  return 0;
}