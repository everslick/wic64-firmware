#include "WiFi.h"
#include "esp_wifi.h"

#include "connection.h"
#include "display.h"

namespace WiC64 {
    const char* Connection::TAG = "CONNECTION";

    extern Connection *connection;
    extern Display *display;

    Connection::Connection() {
        WiFi.mode(WIFI_STA);
        WiFi.setHostname(("WiC64-" + WiFi.macAddress()).c_str());

        WiFi.onEvent(onConnected, ARDUINO_EVENT_WIFI_STA_CONNECTED);
        WiFi.onEvent(onDisconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
        WiFi.onEvent(onGotIpAddress, ARDUINO_EVENT_WIFI_STA_GOT_IP);
    }

    String Connection::getStoredSSID(void) {
        wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
        wifi_config_t wifi_config;
        esp_err_t esp_err;

        esp_wifi_init(&wifi_init_config);

        if ((esp_err = esp_wifi_get_config(WIFI_IF_STA, &wifi_config)) != ESP_OK) {
            ESP_LOGE(TAG, "esp_wifi_get_config() failed: %s", esp_err_to_name(esp_err));
            return "";
        }
        return String((char*) wifi_config.sta.ssid);
    }

    void Connection::onConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
        ESP_LOGI(TAG, "WiFi connected");
        ESP_LOGI(TAG, "SSID: %s %ddbm", getStoredSSID().c_str(), WiFi.RSSI());

        display->SSID(getStoredSSID());
        display->RSSI(WiFi.RSSI());
        display->ip("0.0.0.0");
        display->status("Connected");
    }

    void Connection::onDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
        ESP_LOGI(TAG, "WiFi not connected");

        display->SSID(getStoredSSID());
        display->RSSI(WiFi.RSSI());
        display->ip("0.0.0.0");
        display->status("Connecting...");

        connection->connect();
    }

    void Connection::onGotIpAddress(WiFiEvent_t event, WiFiEventInfo_t info) {
        ESP_LOGI(TAG, "ADDR: %s", connection->ipAddress());
        ESP_LOGI(TAG, "MASK: %s", WiFi.subnetMask().toString().c_str());
        ESP_LOGI(TAG, "GATE: %s", WiFi.gatewayIP().toString().c_str());
        ESP_LOGI(TAG, "DNS1: %s", WiFi.dnsIP().toString().c_str());
        display->ip(connection->ipAddress());
    }

    bool Connection::isConnected() {
        return WiFi.isConnected();
    }

    void Connection::connect() {
        ESP_LOGI(TAG, "Connecting to WiFi network...");
        WiFi.begin();
    }

    const char* Connection::ipAddress() {
        static char ip[16];
        strncpy(ip, WiFi.localIP().toString().c_str(), 16);
        return ip;
    }

    const char *Connection::macAddress() {
        static char mac[18];
        strncpy(mac, WiFi.macAddress().c_str(), 18);
        return mac;
    }
}
