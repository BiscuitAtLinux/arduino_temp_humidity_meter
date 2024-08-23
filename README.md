# arduino_temp_humidity_meter

基于Arduino的温湿度计，通过串口、数码管和MQTT输出结果

使用NodeMCU的连接方式

温湿度传感器 DHT11
 * 3.3V -> +
 * GND -> -
 * D1 -> out

MAX7219 8位数码管
 * 3.3V -> VCC
 * GND -> GND
 * D7 -> DIN
 * D5 -> CLK
 * D2 -> CS