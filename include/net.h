/**
 * WiFi连接及MQTT相关
 */
#ifndef net_h
#define net_h

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <MQTT.h>

// WiFi 相关
const char WIFI_SSID[] = "";
const char WIFI_PASS[] = "";

// MQTT 相关
// https://cloud.bemfa.com/docs/src/mqtt.html 巴法云的要求可以只填私钥
const char MQTT_HOST[] = "bemfa.com";
const int MQTT_PORT = 9501;
const char MQTT_ID[] = "";
const char MQTT_TOPIC[] = "";
// 发送间隔(s)，没必要每次更新温度都发送，但是频率也不能太低，测试30s会导致连接断开
const int MQTT_SEND_INTERVAL_S = 10;

// 初始化WiFi及MQTT
void connect();
void sendToMQTT(float temperature, float humidity);

#endif // net_h