/**
 * 温湿度传感器校准相关
 */

#ifndef calibration_h
#define calibration_h

/**
 * 温度传感器简易线性校准
 * 校准温度 = TEMP_A*原始温度值 + TEMP_B
 */
const float TEMP_A = 1.0;
const float TEMP_B = -1.8;

/**
 * 湿度传感器简易线性校准
 * 校准湿度 = HUMIDITY_A*原始湿度值 + HUMIDITY_B
 */
const float HUMIDITY_A = 1.0;
const float HUMIDITY_B = -1.0;

#endif // calibration_h