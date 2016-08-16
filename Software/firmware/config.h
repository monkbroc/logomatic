/* All hardware configuration macros
 */

/* Animation configuration */
#define SEC(x) ((x) * 1000)

#define DISPLAY_TIME_SECONDS 20

#define CLOUD_ANIMATION_TIME SEC(60*60)
#define STARTUP_ANIMATION_TIME SEC(8)
#define STARTUP_BREATHE_TIME SEC(30)

/* SD Card configuration */
#define GIF_DIRECTORY "/logo/"

/* LED strip configuration */
#define PIXEL_PIN A7
#define PIXEL_COUNT 113
#define PIXEL_TYPE WS2812B

/* Gesture sensor configuration */
#define APDS9960_INT    D2 // Needs to be an interrupt pin

/* SD card configuration and CS pins */
#define SPI_CONFIGURATION 0
#define SD_CHIP_SELECT A2
