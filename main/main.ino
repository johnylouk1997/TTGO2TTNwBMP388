#include <lmic.h>
#include <hal/hal.h>

#include "Temperature.h"  //Include Code For BMP388
#include "TTN_SendJob.h"

//========================================
//          TTN Authentication
//========================================

static const u1_t 
PROGMEM APPEUI[8]={ 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 }; //Must fill with your own appeui, in format lsb
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}

static const u1_t
PROGMEM DEVEUI[8]={ 0x00 , 0x00 , 0x00 , 0x00, 0x00 , 0x00 , 0x00 , 0x00 }; //Must fill with your own deveui, in format lsb
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}

static const u1_t 
PROGMEM APPKEY[16] = {                 ////Must fill with your own appkey, in format msb 
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

//========================================

//========================================
//          TTGO LoRa ESP32 V2.0.0
//URL for Board Manager: https://dl.espressif.com/dl/package_esp32_index.json
//Board Manager search: esp32
//========================================

const lmic_pinmap lmic_pins = {
    .nss = 18, 
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 23,
    .dio = {/*dio0*/ 26, /*dio1*/ 33, /*dio2*/ 32}
};

//========================================


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        

// constants won't change:
const long interval = 60* 60 * 1000;// interval at which to blink (milliseconds)

void setup() {
    Serial.begin(115200);
    Serial.println(F("Starting..."));
    
    // LMIC init
    os_init();

    // Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();

    // Disable link check validation
    LMIC_setLinkCheckMode(0);

    // TTN uses SF9 for its RX2 window.
    LMIC.dn2Dr = DR_SF9;

    // Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
    LMIC_setDrTxpow(DR_SF7,14);

    //BMP388 initialization
    Temperature_Init();

    // Start job
    do_send(&sendjob);
}

void loop(){ 
    unsigned long currentMillis = millis();

    if ((currentMillis - previousMillis) >= interval) {
        previousMillis = currentMillis;
        ESP.restart();
    }  
    os_runloop_once();
}
