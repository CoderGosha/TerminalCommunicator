#include "curl/curl.h"
#include <string>
#include "credential.h"

int ping(){
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
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
  
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}