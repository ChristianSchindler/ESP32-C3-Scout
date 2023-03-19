#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#define ScoutPassword "Dakommsteniedrauf"

bool checkWLAN();

void setup() {
    // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP, which we need

    Serial.begin(115200); //Configures the serial connection over usb with the baudrate
    
    WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    wm.resetSettings(); //Comment this when not debuging

    /** Automatically connect using saved credentials,
    * if connection fails, it starts an access point with the specified name,
    * then goes into a blocking loop awaiting configuration and will return success result
    */
    bool res = wm.autoConnect("ESP32 Configuration Scout", ScoutPassword);//The second string is the password

    if(!res) {
        Serial.println("[Setup]: Failed to connect, restaring the ESP.");
        ESP.restart();
    } 
    else {   
        Serial.println("[Setup]: Connected successfully.");
    }
}

void loop() {
    if(checkWLAN) {
        Serial.println("WLAN: Connected");
    } else {
        Serial.println("WLAN: Not connected");
    }
    vTaskDelay(5000);
}

// Checks if the ESP is still connected to it's WLAN, if not, it trys to reconnect with the old credentials.
// If this doesn't work, it restarts the Scout for a limited time:
#define ConfigPortalTimeOut 100 //in Seconds

bool checkWLAN() {
    Serial.println("[CheckWLAN]: Checking if the chip is still connected to the WLAN.");
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("[CheckWLAN]: Not connected, trying old credentials. If they fail, starting scout");
        WiFiManager wm;
        wm.setTimeout(100);
        bool res = wm.autoConnect("ESP32 Reconfiguration Scout", ScoutPassword);

        if(!res) {
            Serial.println("[CheckWLAN]: Failed to connect");
            return true;
        } 
        else { 
            Serial.println("[CheckWLAN]: Connected successfully.");
            return false;
        }
    }
    return true;
}