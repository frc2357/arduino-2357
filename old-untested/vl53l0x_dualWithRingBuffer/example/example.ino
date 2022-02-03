#include "RingBuffTof.h"

// address we will assign if dual sensor is present

// set the pins to shutdown
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define SHT_LOX1 7
#define SHT_LOX2 6
#define VL53L0X_MAX_DISTANCE 2000
#define RINGBUFFER_LENGTH 6
RingBuffTof tof( SHT_LOX1, SHT_LOX2, VL53L0X_MAX_DISTANCE, RINGBUFFER_LENGTH);
void setup()
{
tof.setup();
}
void loop()
{
tof.update();
}
