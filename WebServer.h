#ifndef ABSTRACT_ARDUINO_WSIF
#define ABSTRACT_ARDUINO_WSIF

#include <string.h>
#include "WebServerResponse.h"
#include "WebServerRequest.h"

#define MAX_HEADER_LINE_LEN 50
#define MAX_HEADER_LINES 10

#define HTML_LINE_ENDING "\r\n"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class WebServer
{
public:
    WebServer(void (*appCallback)(const WebServerRequest&, WebServerResponse&));
    virtual void processNextRequest() = 0;

protected:
    WebServerResponse currentResponse;
    WebServerRequest currentRequest;
    void (*appCallback)(const WebServerRequest&, WebServerResponse&);
    char reqLineBuf[MAX_HEADER_LINE_LEN+1];

    // As appose to doing exspensive copy of WebServerRequest, update existing object
    void resetRequest();
    virtual const char* getNextLine();
    virtual bool parseHeader();
    WebServerRequest& getRequest();
    WebServerResponse& getResponse();

private:
    bool parseFirstLine(const char *const line);

};

#endif
