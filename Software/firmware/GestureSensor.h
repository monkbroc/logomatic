/* Process gestures from the APDS9960 sensor
 */
#pragma once

#include "SparkFun_APDS9960.h"

class GestureSensor {
public:
    GestureSensor();
    void begin();

    int getGesture();

protected:
    static const int processingPeriod;

    static void gestureInterrupt();
    static bool gestureDetected;

    void processSensor();

    SparkFun_APDS9960 sensor;
    int gesture;
};
