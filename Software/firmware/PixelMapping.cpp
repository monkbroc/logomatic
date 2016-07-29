/* Map from 2D coordinates to linear offset on the LED strip */
const int pixelMapping[] = {
  // right arrow
  27, 17,
  25, 17,
  24, 16,
  25, 16,
  27, 16,
  29, 16,
  31, 16,
  27, 15,
  25, 15,

  // top right
  24, 10,
  23, 11,
  22, 12,
  21, 14,
  20, 15,
  18, 14,
  19, 13,
  20, 12,
  21, 11,
  22, 10,
  23, 9,
  24, 8,
  25, 7,
  22, 8,
  21, 9,
  20, 10,
  18, 11,
  17, 12,

  // top arrow
  17, 5,
  17, 7,
  16, 8,
  16, 7,
  16, 5,
  16, 3,
  16, 1,
  15, 5,
  15, 7,

  // top left
  10, 8,
  11, 9,
  12, 10,
  14, 11,
  15, 12,
  16, 14, // center top
  14, 14,
  13, 13,
  12, 12,
  11, 11,
  10, 10,
  9, 9,
  8, 8,
  7, 7,
  8, 10,
  9, 11,
  10, 12,
  11, 14,
  12, 15,

  // left arrow
  5, 15,
  7, 15,
  8, 16,
  7, 16,
  5, 16,
  3, 16,
  1, 16,
  5, 17,
  7, 17,

  // bottom left
  8, 22,
  9, 21,
  10, 20,
  11, 18,
  12, 17,
  14, 18,
  13, 19,
  12, 20,
  11, 21,
  10, 22,
  9, 23,
  8, 24,
  7, 25,
  10, 24,
  11, 23,
  12, 22,
  14, 21,
  15, 20,

  // bottom arrow
  15, 27,
  15, 25,
  16, 24,
  16, 25,
  16, 27,
  16, 29,
  16, 31,
  17, 27,
  17, 25,

  // bottom right
  22, 24,
  21, 23,
  20, 22,
  18, 21,
  17, 20,
  16, 18, // center bottom
  18, 18,
  19, 19,
  20, 20,
  21, 21,
  22, 22,
  23, 23,
  24, 24,
  25, 25,
  24, 22,
  23, 21,
  22, 20,
  21, 18,
  20, 17,

  // center
  18, 16,
  16, 16,
  14, 16,
};

int pixelCoordToLinearOffset(int x, int y)
{
  const int pixelCount = sizeof(pixelMapping)/sizeof(pixelMapping[0])/2;
  for (int i = 0; i < pixelCount; i++) {
    if (pixelMapping[2*i] == x && pixelMapping[2*i+1] == y) {
      return i;
    }
  }
  return -1;
}

