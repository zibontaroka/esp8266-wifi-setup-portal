// File: WiFiSetup.h
#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <ESP8266WebServer.h>

class WiFiSetup {
  public:
    WiFiSetup(const char* apSSID, const char* apPassword);
    void begin();
    void handle();

  private:
    ESP8266WebServer server;
    const char* apSSID;
    const char* apPassword;

    static const char* htmlPage;

    void handleRoot();
    void handleScan();
    void handleConnect();
};

#endif // WIFI_SETUP_H
