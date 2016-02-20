
#include "WebServerRequest.h"

WebServerRequest::WebServerRequest(WebServer &caller)
: webServer(caller)
{
    requestType = NONE;
}

// Returns NULL on error
const char* WebServerRequest::addVar(const char *const key, const char *const val)
{
    return data.addVar(key, val);
}


const char* WebServerRequest::getVarByName(const char *const key)
{
    return data.getVar(key);
}

void WebServerRequest::reset()
{
    requestType = NONE;
}

void WebServerRequest::setRequestType(HTTPRequestType_t typ)
{
    requestType = typ;
}

HTTPRequestType_t WebServerRequest::getRequestType() const
{
    return this->requestType;
}
