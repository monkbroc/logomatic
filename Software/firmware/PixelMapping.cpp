#include "utils.h"
#include <cstdint>

/* Map from 2D coordinates to linear offset on the LED strip */
const uint8_t pixelMapping[] = {
  // right arrow
  14, 9,
  13, 9,
  12, 8,
  13, 8,
  14, 8,
  15, 8,
  16, 8,
  14, 7,
  13, 7,

  // top right
  14, 3,
  13, 4,
  12, 5,
  11, 6,
  10, 7,
  9, 7,
  10, 6,
  11, 5,
  12, 4,
  13, 3,
  14, 2,
  15, 1,
  16, 0,
  13, 2,
  12, 3,
  11, 4,
  10, 5,
  9, 6,

  // top arrow
  9, 2,
  9, 3,
  8, 4,
  8, 3,
  8, 2,
  8, 1,
  8, 0,
  7, 2,
  7, 3,

  // top left
  3, 2,
  4, 3,
  5, 4,
  6, 5,
  7, 6,
  8, 7, // center top
  7, 7,
  6, 6,
  5, 5,
  4, 4,
  3, 3,
  2, 2,
  1, 1,
  0, 0,
  2, 3,
  3, 4,
  4, 5,
  5, 6,
  6, 7,

  // left arrow
  2, 7,
  3, 7,
  4, 8,
  3, 8,
  2, 8,
  1, 8,
  0, 8,
  2, 9,
  3, 9,

  // bottom left
  2, 13,
  3, 12,
  4, 11,
  5, 10,
  6, 9,
  7, 9,
  6, 10,
  5, 11,
  4, 12,
  3, 13,
  2, 14,
  1, 15,
  0, 16,
  3, 14,
  4, 13,
  5, 12,
  6, 11,
  7, 10,

  // bottom arrow
  7, 14,
  7, 13,
  8, 12,
  8, 13,
  8, 14,
  8, 15,
  8, 16,
  9, 14,
  9, 13,

  // bottom right
  13, 14,
  12, 13,
  11, 12,
  10, 11,
  9, 10,
  8, 9, // center bottom
  9, 9,
  10, 10,
  11, 11,
  12, 12,
  13, 13,
  14, 14,
  15, 15,
  16, 16,
  14, 13,
  13, 12,
  12, 11,
  11, 10,
  10, 9,

  // center
  9, 8,
  8, 8,
  7, 8,
};

const uint8_t centerPixels[] = {
  // top right
  14, 3,
  13, 4,
  12, 5,
  11, 6,
  10, 7,
  9, 7,
  10, 6,
  11, 5,
  12, 4,
  13, 3,
  14, 2,
  15, 1,
  16, 0,
  13, 2,
  12, 3,
  11, 4,
  10, 5,
  9, 6,

  // top left
  3, 2,
  4, 3,
  5, 4,
  6, 5,
  7, 6,
  8, 7, // center top
  7, 7,
  6, 6,
  5, 5,
  4, 4,
  3, 3,
  2, 2,
  1, 1,
  0, 0,
  2, 3,
  3, 4,
  4, 5,
  5, 6,
  6, 7,

  // bottom left
  2, 13,
  3, 12,
  4, 11,
  5, 10,
  6, 9,
  7, 9,
  6, 10,
  5, 11,
  4, 12,
  3, 13,
  2, 14,
  1, 15,
  0, 16,
  3, 14,
  4, 13,
  5, 12,
  6, 11,
  7, 10,

  // bottom right
  13, 14,
  12, 13,
  11, 12,
  10, 11,
  9, 10,
  8, 9, // center bottom
  9, 9,
  10, 10,
  11, 11,
  12, 12,
  13, 13,
  14, 14,
  15, 15,
  16, 16,
  14, 13,
  13, 12,
  12, 11,
  11, 10,
  10, 9,

  // center
  9, 8,
  8, 8,
  7, 8,
};

const uint8_t arrowPixels[] = {
  // right arrow
  14, 9,
  13, 9,
  12, 8,
  13, 8,
  14, 8,
  15, 8,
  16, 8,
  14, 7,
  13, 7,

  // top arrow
  9, 2,
  9, 3,
  8, 4,
  8, 3,
  8, 2,
  8, 1,
  8, 0,
  7, 2,
  7, 3,

  // left arrow
  2, 7,
  3, 7,
  4, 8,
  3, 8,
  2, 8,
  1, 8,
  0, 8,
  2, 9,
  3, 9,

  // bottom arrow
  7, 14,
  7, 13,
  8, 12,
  8, 13,
  8, 14,
  8, 15,
  8, 16,
  9, 14,
  9, 13,
};

int pixelCoordToLinearOffset(int x, int y)
{
  const int pixelCount = countof(pixelMapping)/2;
  for (int i = 0; i < pixelCount; i++) {
    if (pixelMapping[2*i] == (uint8_t)x && pixelMapping[2*i+1] == (uint8_t)y) {
      return i;
    }
  }
  return -1;
}

// Is this pixel in the center portion of the logo
bool isCenterPixel(int x, int y) {
  const int pixelCount = countof(centerPixels)/2;
  for (int i = 0; i < pixelCount; i++) {
    if (centerPixels[2*i] == (uint8_t)x && centerPixels[2*i+1] == (uint8_t)y) {
      return true;
    }
  }
  return false;
}

// Is this pixel in one of the arrow portions of the logo
bool isArrowPixel(int x, int y) {
  const int pixelCount = countof(arrowPixels)/2;
  for (int i = 0; i < pixelCount; i++) {
    if (arrowPixels[2*i] == (uint8_t)x && arrowPixels[2*i+1] == (uint8_t)y) {
      return true;
    }
  }
  return false;
}

