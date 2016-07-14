/* Map from 2D coordinates to linear offset on the LED strip */
const int pixelMapping[] = {
  // right arrow
  25, 15,
  27, 16,
  29, 16,
  25, 17,

  // down right
  21, 18,
  22, 20,
  23, 21,
  24, 23,
  25, 25,
  27, 27,
  23, 24,
  21, 23,
  20, 22,
  18, 21,

  // down arrow
  17, 25,
  16, 27,
  16, 29,
  15, 25,

  // down left
  14, 21,
  12, 22,
  11, 23,
  9, 24,
  7, 25,
  5, 27,
  8, 23,
  9, 21,
  10, 20,
  11, 18,

  // left arrow
  7, 17,
  5, 16,
  3, 16,
  7, 15,

  // up left
  11, 14,
  10, 12,
  9, 11,
  8, 9,
  7, 7,
  5, 5,
  9, 8,
  11, 9,
  12, 10,
  14, 11,

  // up arrow
  15, 7,
  16, 5,
  16, 3,
  17, 7,

  // up right
  18, 11,
  20, 10,
  21, 9,
  23, 8,
  25, 7,
  27, 5,
  24, 9,
  23, 11,
  22, 12,
  21, 14,

  // middle
  17, 15,
  15, 15,
  15, 17,
  17, 17,
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

