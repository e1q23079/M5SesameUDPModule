#include "UdpManager.h"

WiFiUDP wifiudp;

IPAddress local_ip;
IPAddress gateway;
IPAddress subnet;

UdpManager::UdpManager(const char* ssid, const char* password,
                       const char* ip_address, uint16_t port,
                       const char* gateway_ip, const char* subnet_mask)
    : ssid(ssid),
      password(password),
      ip_address(ip_address),
      port(port),
      gateway_ip(gateway_ip),
      subnet_mask(subnet_mask) {};

bool UdpManager::begin() {
    local_ip.fromString(ip_address);
    gateway.fromString(gateway_ip);
    subnet.fromString(subnet_mask);

    if (!WiFi.config(local_ip, gateway, subnet)) {
        return false;
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    wifiudp.begin(port);
    return true;
};

String UdpManager::read() {
    char buffer[256];

    int packetSize = wifiudp.parsePacket();

    if (!packetSize) {
        return String("");
    }

    int len = wifiudp.read(buffer, min(packetSize, (int)(sizeof(buffer) - 1)));

    if (len <= 0) {
        return String("");
    }

    buffer[len] = '\0';
    String msg = String(buffer);
    msg.trim();

    return msg;
};