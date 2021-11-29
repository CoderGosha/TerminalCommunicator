#include <string>
#include "../credential.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../timeout.h"

#include <sstream>
#include <iomanip>

#include "httplib.h"

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
  return cli;
}

int client_socket::ping(){
  auto cli = get_client();

  std::string data = "{\"name\" : \"" + get_name() + "\", \"version\" : \"" + get_version() + "\" }";

  auto res = cli.Post("/api/ping/", data.c_str(), "application/json");
  if (res->status == 200);
      return 1;
  
  timeout::increment_error();
  fprintf(stderr, "httplib) failed, code:%i, message: %s\n", res->status, res->body);
  return 0;
}

std::string client_socket::get_events(){
  return "[]";
}

int client_socket::post_event(std::string id, std::string response, int status){
  
  return 0;
}