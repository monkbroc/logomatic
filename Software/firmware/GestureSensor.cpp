#include "GestureSensor.h"
#include "config.h"

const int GestureSensor::processingPeriod = 50; /* ms */

bool GestureSensor::gestureDetected = false;

GestureSensor::GestureSensor()
    : sensor{},
    gesture{DIR_NONE}
{
}

void GestureSensor::begin() {
    pinMode(APDS9960_INT, INPUT);
    // Initialize interrupt service routine
    attachInterrupt(APDS9960_INT, gestureInterrupt, FALLING);

    // Initialize APDS-9960 (configure I2C and initial values)
    if (!sensor.init()) {
        Serial.println("Something went wrong during APDS-9960 init!");
        while(true);
    }

    // Start running the APDS-9960 gesture sensor engine
    if (!sensor.enableGestureSensor(true)) {
        Serial.println("Something went wrong during gesture sensor init!");
        while(true);
    }

    Thread("gesture", [this]() {
        for(;;) {
            processSensor();
            HAL_Delay_Milliseconds(processingPeriod);
        }
    });

    Serial.println("Gesture sensor is now running");
}

int GestureSensor::getGesture() {
    SingleThreadedSection st;
    int ret = gesture;
    gesture = DIR_NONE;
    return ret;
}


void GestureSensor::gestureInterrupt() {
    gestureDetected = true;
}

void GestureSensor::processSensor() {
    if (sensor.isGestureAvailable()) {
        gesture = sensor.readGesture();
    }
}
