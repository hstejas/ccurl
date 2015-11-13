#include <algorithm>
#include "ccurl.hpp"

using namespace ccurl;

std::vector<char> Curl::_buffer;
CURL *Curl::_curl = NULL;

Curl::Curl()
{
    _curl = curl_easy_init();
    if(!_curl)
    {
        CERROR("curl* is invalid");
    }
}

bool Curl::init()
{
    static Curl _curlMain;

    setWriteHandler(&defaultWriteHandler, static_cast<void*>(&_buffer));

    return _curlMain._curl != NULL;
}

Curl::~Curl()
{
    curl_easy_cleanup(_curl);
}

void Curl::setURL(const std::string& url)
{
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
}

void Curl::setFollowLocation(const bool& follow/*=true*/)
{
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, follow?1L:0);
}

void Curl::setUserAgent(const std::string& ua)
{
    curl_easy_setopt(_curl, CURLOPT_USERAGENT, ua.c_str());
}

void Curl::setWriteHandler(writeMemoryHandler wmh, void* data)
{
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, wmh);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, data);
}

size_t Curl::defaultWriteHandler(void *contents, size_t size, size_t nmemb, void *userp)
{
    std::vector<char> *bufp = static_cast< std::vector<char>* >(userp);
    size_t initialSize = bufp->size(); 
    bufp->insert(bufp->end(), static_cast<char*>(contents), static_cast<char*>(contents)+size*nmemb);
    return bufp->size() - initialSize;
}

bool Curl::perform()
{
    _buffer.clear();
    CURLcode res;
    res = curl_easy_perform(_curl);
    if(res != CURLE_OK)
    {
        CERROR("Curl perform() failed: " << curl_easy_strerror(res) << std::endl);
        return false;
    }
    return true;
}

void Curl::print()
{
    std::for_each(_buffer.begin(), _buffer.end(),[](const char& c){std::cout << c;});
}

void Curl::getString(std::string& str)
{
    str.insert(str.end(), _buffer.begin(), _buffer.end());
}

