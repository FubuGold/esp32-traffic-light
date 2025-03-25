#include "state_control.h"
#include "env.h"
#include "net.h"
#include "mqtt.h"
#include <WiFi.h>
#include <Arduino.h>
#include <map>

using State_control::state;
using State_control::traffic_light;

/*==================================================*/

const uint8_t STATE_COUNT = 8;
const int buzzer = 13; // Why
std::map<String, uint64_t> duration = {
    {"red", 7000},
    {"red yellow", 3000},
    {"green", 10000},
    {"green blink1", 500},
    {"green blink2", 500},
    {"green blink3", 500},
    {"green blink4", 500},
    {"yellow", 3000}};
// [led][G = 0, Y = 1, R = 2]
std::vector<uint8_t> start_pin = {35, 36, 37};

traffic_light start("start", start_pin, duration);

String start_state, west_state;

void setup()
{
    Serial.begin(9600);
    // while (!Serial)
    //     ;
    for (int i = 0; i < 3; i++)
    {
        pinMode(start_pin[i], OUTPUT);
    }
    start.set_state(0);
    uint64_t cur = millis();
    start.set_time(cur);

    net::setup();
    // mqtt::setup();
    start_state = start.get_state();
    // mqtt::publish("config/0/input/start", start_state);
    Serial.println("Setup complete");
}

void loop()
{
    // Serial.println("Alive");
    // digitalWrite(start_pin[1], HIGH);
    // delay(3000);
    // digitalWrite(start_pin[1], LOW);
    // delay(3000);
    // net::loop();
    // mqtt::loop();

    if (start.change())
    {
        start_state = start.get_state();
        Serial.print("start ");
        // mqtt::publish("config/0/input/start", start_state);
    }
}