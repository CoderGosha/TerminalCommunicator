#include <curl/curl.h>
#include <string>
#include "../credential.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../timeout.h"

#include <sstream>
#include <iomanip>

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

class client_curl
{
private:
  /* data */
 // int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in);
public:
  client_curl(/* args */);
  ~client_curl();
  int ping();
  std::string get_events();
  int post_event(std::string id, std::string response, int status);
 };

client_curl::client_curl(/* args */)
{
}

client_curl::~client_curl()
{
}

size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    try
    {
        s->append((char*)contents, newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }
    return newLength;
}

int client_curl::ping(){
  std::string url = get_url();
  std::string token = get_token(); 
  
  std::string ping_url = url + "/api/ping/";
  
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    
    std::string data = "{\"name\" : \"" + get_name() + "\", \"version\" : \"" + get_version() + "\" }";

    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, token.c_str());
    chunk = curl_slist_append(chunk, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    
    curl_easy_setopt(curl, CURLOPT_URL, ping_url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str()); 

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      timeout::increment_error();
      }
    if(res == CURLE_OK) {
       long response_code;
       curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
       if (response_code != 200)
          timeout::increment_error();
     }
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}

std::string client_curl::get_events(){
  std::string url = get_url();
  std::string token = get_token(); 
  std::string event_url = url + "/api/event?name=" + get_name().c_str();
  CURL *curl;
  CURLcode res;
  std::string s;

  curl = curl_easy_init();
  if(curl) {
    long response_code;
    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, token.c_str());
    chunk = curl_slist_append(chunk, "Accept: application/json");
    chunk = curl_slist_append(chunk, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    
    curl_easy_setopt(curl, CURLOPT_URL, event_url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
         timeout::increment_error();
         return NULL;
      }

    if(res == CURLE_OK) {
       long response_code;
       curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
       if (response_code != 200)
          timeout::increment_error();
     }

    curl_easy_cleanup(curl);
  }
  return s;
}

int client_curl::post_event(std::string id, std::string response, int status){
  std::string url = get_url();
  std::string token = get_token(); 
  
  std::string ping_url = url + "/api/event/";
  std::string status_str = std::to_string(status);
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    std::string response_escape = escape_json(response); 
    std::string data = "{\"id\" : \"" + id + "\", \"response\" : \"" + response_escape + "\" , \"success\" : " + status_str + "}";

    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, token.c_str());
    chunk = curl_slist_append(chunk, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    
    curl_easy_setopt(curl, CURLOPT_URL, ping_url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str()); 

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      timeout::increment_error();
      return -1;
    }

    if(res == CURLE_OK) {
       long response_code;
       curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
       if (response_code != 200)
          timeout::increment_error();
     }
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}

