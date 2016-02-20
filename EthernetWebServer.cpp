#include "EthernetWebServer.h"

EthernetWebServer::EthernetWebServer(EthernetServer &ethServ, void(*appCallback)(const WebServerRequest&, WebServerResponse&))
 : WebServer(appCallback), server(ethServ)
{
}

void EthernetWebServer::processNextRequest()
{
    Serial.println("proc");
    client = server.available();
    Serial.println(F("got client"));
    if (client)
    {
        if (client.connected() && client.available())
        {
            // Reset request object
            getRequest().reset();
            // Parse the header
            if(parseHeader())
            {
                // Launch the application through its registered callback
                (*appCallback)(getRequest(), getResponse());
            }

        }
        client.stop();
    }
}

// Returns NULL on error
const char* EthernetWebServer::getNextLine()
{
    uint16_t pos=0;
    // Should be 2 \r\n
    uint16_t endLen = strlen(HTML_LINE_ENDING);
    // Dont forget about \0 ending
    for (int i=0; i < MAX_HEADER_LINE_LEN && client.available(); i++)
    {
        reqLineBuf[i] = client.read();
        //End of line found before buffer filled
        if (i >= endLen-1 && !strncmp(&reqLineBuf[i+1-endLen], HTML_LINE_ENDING, endLen))
        {
            //terminate the string
            reqLineBuf[i+1] = '\0';
            break;
        }

        // Last iteration, EOL not found
        if (i == MAX_HEADER_LINE_LEN-1)
        {
            while(client.read() != '\n');
            strncpy(&reqLineBuf[MAX_HEADER_LINE_LEN-endLen], HTML_LINE_ENDING, endLen+1);
        }
    }
    if (!client.connected()) return NULL;
    return reqLineBuf;
}
