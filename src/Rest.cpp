#include "rest/Rest.hpp"

const std::string Rest::baseUrl = "https://XXXXXXX.XXX/";

CURL *Rest::getCurlForUrl(std::string url, HttpRequest request, void *readBuffer) {
    CURL *curl;
    CURLcode res;

    struct curl_slist *headers = NULL;
    curl_slist_append(headers, "Content-Type: application/json");
    curl_slist_append(headers, "charsets: utf-8");
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_HEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        if (request == HttpRequestGet) {
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<std::string *>(readBuffer));
        } else if (request == HttpRequestPost || request == HttpRequestPut) {
            if (request == HttpRequestPost) {
                curl_easy_setopt(curl, CURLOPT_POST, 1L);
            } else if (request == HttpRequestPut) {
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            }

            curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
            curl_easy_setopt(curl, CURLOPT_READDATA, static_cast<struct Writer *>(readBuffer));
        }
     
    }

    return curl;
}

std::string Rest::getWithUrl(std::string urlExtension) {
    std::string readBuffer;

    CURL *curl = getCurlForUrl(baseUrl + urlExtension, HttpRequestGet, &readBuffer);
    CURLcode res;

    if (curl) {
        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            char *contentType;
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &contentType);

            if ((res == CURLE_OK) && contentType) {
                curl_easy_cleanup(curl);
                return readBuffer;
            }
        }
    }

    return "";
}

bool Rest::postToUrl(std::string urlExtension, std::string params) {
    struct Writer writer;
    writer.readptr = params.c_str();
    writer.sizeleft = (long)strlen(writer.readptr);

    CURL *curl = getCurlForUrl(baseUrl + urlExtension, HttpRequestPost, &writer);
    CURLcode res;

    if (curl) {
        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            char *contentType;
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &contentType);
            
            if ((res == CURLE_OK) && contentType) {
                return true;
            }
        }
    }

    return false;
}

bool Rest::putToUrl(std::string urlExtension, std::string params) {
    struct Writer writer;
    writer.readptr = params.c_str();
    writer.sizeleft = (long)strlen(writer.readptr);

    CURL *curl = getCurlForUrl(baseUrl + urlExtension, HttpRequestPut, &writer);
    CURLcode res;

    if (curl) {
        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            char *contentType;
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &contentType);

            if ((res == CURLE_OK) && contentType) {
                return true;
            }
        }
    }

    return false;
}

int main () {

}
