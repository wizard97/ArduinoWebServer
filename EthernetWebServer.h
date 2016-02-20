#ifndef ARDUINO_ETHERNET_WSIF
#define ARDUINO_ETHERNET_WSIF

#include <string.h>
#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include "WebServerResponse.h"
#include "WebServerRequest.h"
#include "WebServer.h"

#include "Arduino.h"

class EthernetWebServer : public WebServer
{
private:
    EthernetServer server;
    EthernetClient client;

protected:
    const char* getNextLine();

public:
    EthernetWebServer(EthernetServer &ethServ, void (*appCallback)(const WebServerRequest&, WebServerResponse&));
    void processNextRequest();

};


#endif
