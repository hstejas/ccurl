#ifndef CCURL_CURL_HPP
#define CCURL_CURL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>

#define CERROR(x)  do{std::cerr << "[ERROR] " << x << std::endl;}while(0);
#define CWARN(x) do{std::cout << "[WARN] " << x << std::endl;}while(0)
#define CINFO(x) do{std::cout << "[INFO] " << x << std::endl;}while(0)

namespace ccurl
{
namespace UserAgent
{
   const std::string Firefox = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:35.0) Gecko/20100101 Firefox/35.0";
   const std::string Chrome = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2227.0 Safari/537.36A";
}
typedef size_t (*writeMemoryHandler)(void */*contents*/, size_t /*size*/, size_t /*nmemb*/, void */*userp*/);
class Curl
{
public:
    static bool init();
    static void setURL(const std::string& url);
    static void setFollowLocation(const bool& follow=true);
    static void setUserAgent(const std::string& ua);
    static void setWriteHandler(writeMemoryHandler wmhi, void* data);
    
    static bool perform();

    static void print();
    static void getString(std::string& str);


protected:
    Curl();
    ~Curl();

    static size_t defaultWriteHandler(void *contents, size_t size, size_t nmemb, void *userp);

    static writeMemoryHandler _writeMemoryHandler;

    static std::vector<char> _buffer;
    static CURL *_curl;
};
}
#endif //CCURL_CURL_HPP
