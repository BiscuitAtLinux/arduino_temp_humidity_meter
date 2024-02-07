/**
 * 基于Arduino的温湿度计，通过串口和数码管输出结果
 */
#include <Arduino.h>
#include <DHT_U.h>
#include <LedControl.h>

/**
 * 温湿度传感器 DHT11 1-wire连接方式
 * 3.3V -> +
 * GND -> -
 * D1 -> out
 */
DHT dht(D1, DHT11);

/*
 * MAX7219 8位数码管 SPI兼容连接方式
 * 3.3V -> VCC
 * GND -> GND
 * D7 -> DIN
 * D5 -> CLK
 * D2 -> CS
 */
LedControl lc = LedControl(D7, D5, D2, 8);

void setup()
{
  // 初始化温湿度传感器
  dht.begin();

  // 初始化串口
  Serial.begin(9600);

  // 初始化数码管
  lc.shutdown(0, false);
  // 亮度可以低一些，晚上不耀眼
  lc.setIntensity(0, 0);
  lc.clearDisplay(0);
}

void loop()
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.printf("%.1f\t%.0f%%\n", t, h);

  // 有时候会测量失败，特别是刚启动的时候，如果失败就不更新显示
  if (isnan(t) || isnan(h))
  {
    delay(1000);
    return;
  }

  // 显示温度，保留1位小数
  int td = (t + 0.05) * 10;
  // 显示在左边，从右数第5位开始展示
  for (int i = 5; i < 8; td /= 10, i++)
  {
    bool dot = false;
    if (i == 6)
    {
      dot = true;
    }
    if (td > 0)
    {
      lc.setChar(0, i, char(td % 10 + '0'), dot);
    }
    else
    {
      lc.setChar(0, i, ' ', false);
    }
  }
  // 输出一个c代表摄氏度
  lc.setChar(0, 4, 'C', false);

  // 湿度测量分辨率低，所以输出整数就行
  int hd = h;
  for (int i = 1; i < 4; hd /= 10, i++)
  {
    if (hd > 0)
    {
      lc.setChar(0, i, char(hd % 10 + '0'), false);
    }
    else
    {
      lc.setChar(0, i, ' ', false);
    }
  }
  // 输出一个H代表湿度
  lc.setChar(0, 0, 'H', false);

  delay(1000);
}