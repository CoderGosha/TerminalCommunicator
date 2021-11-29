
class GetProvider
{
private:
    /* data */
public:
    GetProvider(/* args */);
    ~GetProvider();
    int exec(std::string& id, std::string request, std::string& response);
};

GetProvider::GetProvider(/* args */)
{
}

GetProvider::~GetProvider()
{
}

int GetProvider::exec(std::string& id, std::string request, std::string& response){
  int status = 0;
    
  // CURL *curl;
  // CURLcode res;
  // std::string s;

  // curl = curl_easy_init();
  // if(curl) {
  //   long response_code;
  //   struct curl_slist *chunk = NULL;
  //   curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    
  //   curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
  //   curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
  //   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  //   curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:62.0) Gecko/20100101 Firefox/62.0");
  //   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
  //   curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

  //   /* Perform the request, res will get the return code */
  //   res = curl_easy_perform(curl);
  //   /* Check for errors */
  //   if(res != CURLE_OK) {
  //     fprintf(stderr, "curl_easy_perform() failed: %s\n",
  //             curl_easy_strerror(res));
  //        timeout::increment_error();
  //        return NULL;
  //     }

  //   if(res == CURLE_OK) {
  //      long response_code;
  //      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
  //      if (response_code != 200) 
  //      {
  //         timeout::increment_error();
  //         status = 0;
  //       }
  //       else
  //           status = 1;
  //    }

  //   curl_easy_cleanup(curl);
  //   }
  
    //response = s;
    return status;
}