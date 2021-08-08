#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>

#include "grove_temp_hum.h"
#include "grove_digital_light.h"
#include "grove_airquality_tp401a.h"
#include "secrets.h"

GroveTempHum *sensor_temp_hum;
GroveDigitalLight *sensor_light;
GroveAirquality *sensor_air;
float temperature = 0.0f;
float humidity = 0.0f;
uint32_t lux = 0;
int air = 0;
uint32_t last_time;

void setup()
{
    pinMode(15, OUTPUT);
    digitalWrite(15, 1); // Power up grove sensors
    sensor_temp_hum = new GroveTempHum(14);
    sensor_light = new GroveDigitalLight(4, 5);
    sensor_air = new GroveAirquality(0);
    sensor_air->on_power_on();
    last_time = millis() - 60000;
    Serial.begin(115200);
    Serial.println("setup done");
}

// void fpm_wakup_cb_func(void) {
//     Serial.println("Light sleep is over, either because timeout or external interrupt");
//     Serial.flush();
// }

// void sleep() {
//     extern os_timer_t *timer_list;
//     timer_list = nullptr;
//     // enable light sleep
//     wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
//     wifi_fpm_open();

//     wifi_fpm_set_wakeup_cb(fpm_wakup_cb_func);
//     // sleep for 10 seconds
//     long sleepTimeMilliSeconds = 10e3;
//     wifi_fpm_do_sleep(sleepTimeMilliSeconds * 1000);
//     // timed light sleep is only entered when the sleep command is
//     // followed by a delay() that is at least 1ms longer than the sleep
//     delay(sleepTimeMilliSeconds + 1);
// }

void initWifi() {
    WiFi.mode(WIFI_STA);
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
    }
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("WiFi connected, IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    uint32_t t = millis();
    if (t - last_time > 60000) {
        last_time = t;
        sensor_temp_hum->read_temperature(&temperature);
        sensor_temp_hum->read_humidity(&humidity);
        sensor_light->read_lux(&lux);
        sensor_air->read_quality(&air);
        Serial.print(temperature);
        Serial.print(" - ");
        Serial.print(humidity);
        Serial.print(" - ");
        Serial.print(lux);
        Serial.print(" - ");
        Serial.print(air);
        Serial.println("");

        initWifi();

        WiFiClient client;
        HTTPClient http;
        String json;
        DynamicJsonDocument doc(1024);
        doc["temperature"] = temperature;
        doc["humidity"] = humidity;
        doc["lux"] = lux;
        doc["air"] = air;
        serializeJson(doc, json);
        http.setTimeout(5000);
        http.begin(client, "http://192.168.1.34:6000/wio_link_sensors");
        http.addHeader("Content-Type", "application/json");
        int httpResponseCode = http.POST(json);
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        http.end(); // Free resources
        Serial.println("");
    }
    // sleep();
}
