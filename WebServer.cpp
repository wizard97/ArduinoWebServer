#include "WebServer.h"

WebServer::WebServer(void (*appCallback)(const WebServerRequest&, WebServerResponse&))
: currentRequest(*this), currentResponse(*this)
{
    this->appCallback = appCallback;
    memset(reqLineBuf, '\0', MAX_HEADER_LINE_LEN);
}

// As appose to doing exspensive copy of WebServerRequest, update existing object
void WebServer::resetRequest()
{
    currentRequest.reset();
}

const char* WebServer::getNextLine()
{
    // Sensible default
    strncpy(reqLineBuf, HTML_LINE_ENDING,
            MIN(MAX_HEADER_LINE_LEN, sizeof(HTML_LINE_ENDING)));
    return reqLineBuf;
}

bool WebServer::parseHeader()
{
    uint16_t num_lines = 0;
    const char* line = getNextLine();

    if (!line) return false;

    uint16_t len = strlen(line);

    // Parse header while lines availible and havent exceeder MAX_LINES,
    // and not on last heder line
    while(num_lines < MAX_HEADER_LINES && strcmp(line, HTML_LINE_ENDING))
    {
        Serial.print(line);

        // First line
        if (!num_lines && !parseFirstLine(line)) return false;

        line = getNextLine();
        if (!line) return false;

        len = strlen(line);
        num_lines++;
    }
    return true;
}

bool WebServer::parseFirstLine(const char *const line)
{
    if (!strncmp(line, "GET", MIN(3, MAX_HEADER_LINE_LEN))) currentRequest.setRequestType(GET);
    else if (!strncmp(line, "POST", MIN(4, MAX_HEADER_LINE_LEN))) currentRequest.setRequestType(POST);
    else
    {
        //Set error
        return false;
    }
    return true;
}

WebServerRequest& WebServer::getRequest()
{
    return currentRequest;
}

WebServerResponse& WebServer::getResponse()
{
    return currentResponse;
}
