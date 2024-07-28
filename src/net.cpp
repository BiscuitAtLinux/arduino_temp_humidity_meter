/**
 * WiFi连接及MQTT相关
 */
#include "net.h"

WiFiClient wifi;
MQTTClient client;
int failCount = 0;
unsigned long lastSend = 0;

// 连接Wifi和MQTT
void connect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting mqtt ...");
  client.begin(MQTT_HOST, MQTT_PORT, wifi);
  while (!client.connect(MQTT_ID, "", ""))
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
}

// 向MQTT发送温湿度
void sendToMQTT(float temperature, float humidity)
{
  // 首次发送后，控制发送频率
  if (lastSend > 0 && millis() - lastSend < MQTT_SEND_INTERVAL_S * 1000)
  {
    return;
  }
  char msg[16];
  sprintf(msg, "#%.1f#%.0f", temperature, humidity);
  unsigned long start = millis();
  if (client.publish(MQTT_TOPIC, msg))
  {
    Serial.printf("MQTT succ, cost %lu ms\n", millis() - start);
    lastSend = millis();
  }
  else
  {
    Serial.printf("MQTT fail, cost %lu ms\n", millis() - start);
    failCount++;
    // 如果累计失败3次，重新执行连接
    if (failCount >= 3)
    {
      connect();
      failCount = 0;
    }
  }
}
