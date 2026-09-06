#include <Arduino.h>
#include <WiFi.h>
#include <EEPROM.h>
#include "drv/eeprom.h"
#include "wlanMsg.h"
#include "serialMsg.h"
#include "esp32cam.h"
unsigned long currentT;
uint8_t g_transmitMode;
void setup() {
  delay(1000);
  EEPROM.begin(sizeof(EEPROM_DATA_S));
  eepromApi::read(&g_transmitMode, OFFSET(EEPROM_DATA_S, transmitMode), sizeof(g_transmitMode));
#if defined(CYMPLE_TRANSMIT_WIRE)
  // ===== WIRED(WIRE) firmware =====
  // Streams frames over USB serial (Serial) to the PC CympleApp.
  // No WiFi required. Built by [env:xiao-esp32s3-wire].
  g_transmitMode = TRANSMIT_MODE_WIRE_E;
#else
  // ===== WIRELESS firmware (default) =====
  g_transmitMode = TRANSMIT_MODE_WIRELESS_E;
  if(TRANSMIT_MODE_MAX_E <= g_transmitMode){
    g_transmitMode = TRANSMIT_MODE_WIRELESS_E;
  }
#endif
  pserialObj = new serialClass();
#if !defined(CYMPLE_TRANSMIT_WIRE)
  // Wireless firmware: init WiFi/UDP comms object.
  pwlanMsgObj = new wlanMsgClass();
  serial_writelog("CympleEye WLAN Init!\r\n");
#else
  // Wired firmware: do NOT init WiFi/AsyncUDP - their core log output
  // would pollute the serial image stream. pwlanMsgObj stays NULL;
  // serialMsgCallback guards WIFI_CONFIG against NULL.
  pwlanMsgObj = NULL;
#endif
  pCamera = new cameraClass();
  serial_writelog("CympleEye Camera Init!\r\n");
  delay(1000);
}

void loop() {
  currentT = millis();
  pserialObj->runFrame(currentT);
#if !defined(CYMPLE_TRANSMIT_WIRE)
  if(pwlanMsgObj->runFrame(currentT)){
    return;
  }
#endif
  if(pCamera->runFrame()){
    delay(1000);
    return;
  }
  delay(5);
}
