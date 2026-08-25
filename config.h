#ifndef CONFIG_H
#define CONFIG_H

/******************************************************
 * MAV Smart Garden
 * Configuración general del sistema
 ******************************************************/

//======================================================
// VERSION
//======================================================

#define PROJECT_NAME        "MAV Smart Garden"
#define PROJECT_VERSION     "0.1.0"

//======================================================
// I2C
//======================================================

#define I2C_SDA             8
#define I2C_SCL             9

//======================================================
// ACTUADORES
//======================================================

#define PIN_FAN             4
#define PIN_PUMP            5
#define PIN_GROW_LIGHT      6

#define ACTUATOR_ON  HIGH
#define ACTUATOR_OFF LOW

//======================================================
// ADS1115
//======================================================

#define SOIL_SENSOR_CHANNEL 0

//======================================================
// CALIBRACIÓN SENSOR DE HUMEDAD
//======================================================

#define SOIL_RAW_WET   7000
#define SOIL_RAW_DRY   17250

//======================================================
// OLED
//======================================================

#define SCREEN_WIDTH        128
#define SCREEN_HEIGHT       64

#define OLED_ADDRESS        0x3C

//======================================================
// BME280
//======================================================

#define BME280_ADDRESS      0x76

//======================================================
// WIFI
//======================================================

#define WIFI_SSID           "Cudy-0294"
#define WIFI_PASSWORD       "10978078"

//======================================================
// AUTOMATIZACIÓN
//======================================================

// Temperatura para activar el ventilador
#define FAN_ON_TEMP         28.0f
#define FAN_OFF_TEMP        26.0f

// Humedad mínima del suelo (%)
#define SOIL_MIN            30

// Tiempo de riego (ms)
#define PUMP_TIME           10000

//======================================================
// REFRESCO
//======================================================

#define SENSOR_INTERVAL     2000
#define DISPLAY_INTERVAL    1000
#define WEB_INTERVAL        1000

//======================================================
// TELEMETRÍA
//======================================================

#define TELEMETRY_INTERVAL 60000

//======================================================
// API
//======================================================
#define API_HOST "192.168.10.53"
#define API_PORT 8000
#define API_TELEMETRY_PATH "/api/telemetry"

#endif