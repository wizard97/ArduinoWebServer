#ifndef WEB_SERVER_REQUEST
#define WEB_SERVER_REQUEST

#include <string.h>
#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include "KeyValueData.h"

class WebServer;

typedef enum
{
    GET,
    POST,
    NONE
} HTTPRequestType_t;

class WebServerRequest
{
    private:
        WebServer &webServer;
        HTTPRequestType_t requestType;
        KeyValueData data;
    public:
        WebServerRequest(WebServer &caller);
        const char* addVar(const char *const key, const char *const val);
        const char* getVarByName(const char *const key);
        void setRequestType(HTTPRequestType_t typ);
        HTTPRequestType_t getRequestType() const;
        void reset();
};


#endif
