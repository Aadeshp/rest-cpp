#ifndef WPNETWORK_H_
#define WPNETWORK_H_

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <sstream>

/*
 * HttpRequest Enum For Running Calls On HttpRequest Provided
 */
enum HttpRequest {
    HttpRequestGet,
    HttpRequestPost,
    HttpRequestPut
};

/*
 * Networking Class That Supports HTTP Requests:
 *      - POST
 *      - GET
 *      - PUT
 */
class Rest {
    private:
        // Base URL That This Network Class Will Be Communicating With
        static const std::string baseUrl;

        // Write Callback Function For GET Requests
        static inline int write_callback(void *data, size_t size, size_t nmemb, void *buffer) {
            if (buffer != NULL) {
                (static_cast<std::string *>(buffer))->append(static_cast<char *>(data), size * nmemb);

                return size * nmemb;
            }

            return 0;
        }
        
        // Writer Structure For Sending Parameters For POST/PUT Requests
        struct Writer {
            const char *readptr;
            long sizeleft;
        };

        // Read Callback Function For POST/PUT Requests
        static size_t read_callback(void *data, size_t size, size_t nmemb, void *buffer) {
            struct Writer *writer = static_cast<struct Writer *>(buffer);

            if (size * nmemb < 1) {
                return 0;
            }

            if (writer->sizeleft) {
                *(static_cast<char *>(data)) = writer->readptr[0];
                writer->readptr++;
                writer->sizeleft--;

                return 1;
            }

            return 0;
        }

        // Creates And Returns CURL Pointer Instance Based On URL Extension, HttpRequest, And Reader/Writer
        CURL *getCurlForUrl(std::string, HttpRequest, void *);

    public:
        // Constructor
        Rest() {}
        
        // Deconstructor
        ~Rest() {}
        
        /*
         * HTTP GET Request To URL Extension Provided
         * Format:
         *      - Base URL - http://somewebsite.com/
         *      - URL Extension - users/
         *
         *      Retrieves GET Request Response For http://somewebsite.com/users/
         */
        std::string getWithUrl(std::string);

        /*
         * HTTP POST Request To URL Extension and Parameters Provided
         *
         * Returns boolean Based On If Request Was Status Code: 200 Or Not
         */
        bool postToUrl(std::string, std::string);

        /*
         * HTTP PUT Request To URL Extension And Parameters Provided
         *
         * Returns boolean Based On If Request Was Status Code: 200 Or Not
         */
        bool putToUrl(std::string, std::string);
};

#endif
