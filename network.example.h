// Modify this file, and rename it to "network.h"

#ifndef network_h
#define network_h

#include <WiFiWebServer_RTL8720.h>

#define DEBUG_WIFI_WEBSERVER_PORT Serial
#define _WIFI_LOGLEVEL_           3

#define BOARD_TYPE      "Rtlduino RTL8720DN"
#ifndef BOARD_NAME
  #if defined(ARDUINO_BOARD)
    #define BOARD_NAME    ARDUINO_BOARD
  #elif defined(BOARD_TYPE)
    #define BOARD_NAME    BOARD_TYPE
  #else
    #define BOARD_NAME    "Unknown Board"
  #endif
#endif

#define SHIELD_TYPE   "RTL8720DN"

// Configure these values
#define WIFI_NET_SSID "<your network name>"
#define WIFI_NET_PASS "<your network pass>"

#define HTTP_PORT 80

#endif
