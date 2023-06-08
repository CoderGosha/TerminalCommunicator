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

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include "Poco/JSON/Object.h"


using namespace Poco::Net;
using namespace Poco;


std::string escape_json(const std::string &s) {
    std::ostringstream o;
    for (auto c = s.cbegin(); c != s.cend(); c++) {
        if (*c == '"' || *c == '\\' || ('\x00' <= *c && *c <= '\x1f')) {
            o << "\\u"
              << std::hex << std::setw(4) << std::setfill('0') << (int) *c;
        } else {
            o << *c;
        }
    }
    return o.str();
}

class communicator_client {
private:
    /* data */
    void SetHeader(HTTPRequest& request);

public:
    communicator_client(/* args */);

    ~communicator_client();

    int ping();

    std::string get_events();

    int post_event(std::string id, std::string response, int status);
};

communicator_client::communicator_client(/* args */) {
}

communicator_client::~communicator_client() {
}

void communicator_client::SetHeader(HTTPRequest& request) {
    std::string token = get_token();
    request.setContentType("application/json");
    request.add("Authorization",token.c_str());
    request.add("Accept","application/json");
}

//bool doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request,
//               Poco::Net::HTTPResponse& response)
//{
//    session.sendRequest(request);
//    std::istream& rs = session.receiveResponse(response);
//    std::cout << response.getStatus() << " " << response.getReason() << std::endl;
//    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
//    {
//        std::ofstream ofs("Poco_banner.jpg",std::fstream::binary);
//        StreamCopier::copyStream(rs, ofs);
//        return true;
//    }
//    else
//    {
//        //it went wrong ?
//        return false;
//    }
//}

int communicator_client::ping() {
    Poco::URI uri (  get_url() ) ;
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPResponse response;
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST,
                                   "api/ping/","1.1"); //initializing request body
    SetHeader(request);
    Poco::JSON::Object post_body;

    //post_body.set("name", get_name());
    //post_body.set("version", get_version());
    std::stringstream ss;
    //post_body.stringify(ss);

    std::ostream &oStream = session.sendRequest(request);// sends request, returns open stream
    std::istream &iStream = session.receiveResponse(response);

    //auto res = cli.Post("/api/ping/", data.c_str(), "application/json");
    //if (res->status == 200){
    //    return 1;
    //}
    timeout::increment_error();
    //LogPrint("Ping failed, code:" + std::to_string(res->status) + "message:" + res->body);
    return 0;
}

std::string communicator_client::get_events() {
    LogPrint("Check events");
    std::string response = "[]";
//  auto cli = get_client();
//  auto url_event = "/api/event?name=" + get_name() + "&long=true";
//  auto res = cli.Get(url_event.c_str());
//  if (res->status == 200)
//    {
//      LogPrint("Events: " + std::to_string(res->status)+ ", body:" + res->body);
//      //response = res->body;
//      return res->body;
//    }
    timeout::increment_error();
    //LogPrint("Get_events failed, code:" + std::to_string(res->status) + "message:" + res->body);
    return response;
}

int communicator_client::post_event(std::string id, std::string response, int status) {
//  auto cli = get_client();
//
//  std::string status_str = std::to_string(status);
//  std::string response_escape = escape_json(response);
//  std::string data = "{\"id\" : \"" + id + "\", \"response\" : \"" + response_escape + "\" , \"success\" : " + status_str + "}";
//
//  auto res = cli.Post("/api/event/", data.c_str(), "application/json");
//  if (res->status == 200){
//      return 1;
//  }
    timeout::increment_error();
    //LogPrint("Post_events failed, code:" + std::to_string(res->status) + "message:" + res->body);
    return 0;
}