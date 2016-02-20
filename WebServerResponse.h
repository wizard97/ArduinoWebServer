#ifndef WEB_SERVER_RESPONSE
#define WEB_SERVER_RESPONSE

#include <string.h>
#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include "KeyValueData.h"

class WebServer;

typedef enum HTTP_RESPONSE_CODE
{
    OK = 200,
    INTERNAL_SERVER_ERROR = 500

} HTTP_RESPONSE_CODE;

class WebServerResponse
{
    private:
        KeyValueData input;
        WebServer &webServer;
    public:
        WebServerResponse(WebServer &caller);

};


#endif
