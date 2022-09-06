#include <SPI.h>
#include <WiFi.h>

#include "screen.h"
#include "network.h"

#define ARG_ON  "on"
#define ARG_OFF "off"

// Bit mapping
#define ENTER_BIT_IDX        0
#define DONOTDISTURB_BIT_IDX 1
#define MEETING_BIT_IDX      2

Adafruit_ILI9341 *gfx = new Adafruit_ILI9341(TFT_CS, TFT_DC);

WiFiWebServer server(HTTP_PORT);

int status = WL_IDLE_STATUS;

byte prevMessageStatus = 0xFF;
byte currMessageStatus = 0x00;

void clear_screen() {
  gfx->fillScreen(ILI9341_BLACK);
  gfx->setCursor(0, 0);
  yield();
}

void connecting() {
  clear_screen();
  gfx->setTextSize(1);
  gfx->setTextColor(ILI9341_WHITE);

  String fv = WiFi.firmwareVersion();
  gfx->print("WiFi Firmware ");

  if (fv == LATEST_RTL8720_FIRMWARE) {
    gfx->println(fv);
   } else {
    gfx->print(fv);
    gfx->println(" (upgradable)");
  }

  gfx->print("Connecting to ");
  gfx->print(WIFI_NET_SSID);
}

void connection_failed() {
  clear_screen();
  gfx->setTextSize(1);
  gfx->setTextColor(ILI9341_RED);
  gfx->println("WiFi Connection Failed :(");
}

void please_enter() {
  clear_screen();
  gfx->setCursor(8, 100);
  gfx->setTextSize(4);
  gfx->setTextColor(ILI9341_GREEN);
  gfx->println("Please Enter!");
}

void do_not_disturb() {
  clear_screen();
  gfx->setCursor(40, 100);
  gfx->setTextSize(3);
  gfx->setTextColor(ILI9341_ORANGE);
  gfx->println("Do Not Disturb");
  gfx->println();

  gfx->setCursor(80, 220);
  gfx->setTextSize(2);
  gfx->setTextColor(ILI9341_WHITE);
  gfx->print("Thank you XD");
}

void meeting_in_progress() {
  clear_screen();
  gfx->setCursor(80, 100);
  gfx->setTextSize(6);
  gfx->setTextColor(ILI9341_RED);
  gfx->println("Stop!");

  gfx->setCursor(50, 220);
  gfx->setTextSize(2);
  gfx->setTextColor(ILI9341_WHITE);
  gfx->print("Meeting in progress");
}

void handleBlank() {
  prevMessageStatus = currMessageStatus;
  currMessageStatus = 0x00;
  server.send(200, "text/html", "OK");
}

void handleEnter() {
  prevMessageStatus = currMessageStatus;
  bool bitValue = (server.argName(0) == "on") ? true
    : (server.argName(0) == "off") ? false
      : bitRead(currMessageStatus, ENTER_BIT_IDX);
  bitWrite(currMessageStatus, ENTER_BIT_IDX, bitValue);
  server.send(200, "text/html", "OK");
}

void handleDoNotDisturb() {
  prevMessageStatus = currMessageStatus;
  bool bitValue = (server.argName(0) == "on") ? true
    : (server.argName(0) == "off") ? false
      : bitRead(currMessageStatus, DONOTDISTURB_BIT_IDX);
  bitWrite(currMessageStatus, DONOTDISTURB_BIT_IDX, bitValue);
  server.send(200, "text/html", "OK");
}

void handleMeeting() {
  prevMessageStatus = currMessageStatus;
  bool bitValue = (server.argName(0) == "on") ? true
    : (server.argName(0) == "off") ? false
      : bitRead(currMessageStatus, MEETING_BIT_IDX);
  bitWrite(currMessageStatus, MEETING_BIT_IDX, bitValue);
  server.send(200, "text/html", "OK");
}

void handleNotFound() {
  server.send(404, "text/plain", "");
}

void setup() {
  // Init Serial
  Serial.begin(115200);
  while (!Serial);

  // Init the screen
  gfx->begin();
  gfx->setRotation(1);

  // Init WiFi
  while (status != WL_CONNECTED) {
    connecting();

    status = WiFi.begin(WIFI_NET_SSID, WIFI_NET_PASS);
    for (int i = 0; i < 10; i++) {
      gfx->print(".");
      delay(1000);
    }
  }

  if (status != WL_CONNECTED) {
    connection_failed();
    while(true);
  }

  gfx->println();
  gfx->print("Connected with IP address ");
  gfx->println(WiFi.localIP());

  gfx->print("Webserver version ");
  gfx->println(WIFI_WEBSERVER_RTL8720_VERSION);

  // Set up the http routes
  server.on("/blank", handleBlank);
  server.on("/enter", handleEnter);
  server.on("/meeting", handleMeeting);
  server.on("/donotdisturb", handleDoNotDisturb);
  server.onNotFound(handleNotFound);

  // Start the server
  server.begin();
  gfx->print("Server started on port ");
  gfx->println(HTTP_PORT);
}

void loop() {
  server.handleClient();

  if (prevMessageStatus != currMessageStatus) {
    if (bitRead(currMessageStatus, MEETING_BIT_IDX)) { return meeting_in_progress(); }
    if (bitRead(currMessageStatus, DONOTDISTURB_BIT_IDX)) { return do_not_disturb(); }
    if (bitRead(currMessageStatus, ENTER_BIT_IDX)) { return please_enter(); }
    return clear_screen();
  }
}
