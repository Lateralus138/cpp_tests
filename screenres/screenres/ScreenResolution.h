#pragma once
#ifndef SCREENRESOLUTION_H
#define SCREENRESOLUTION_H
struct Screen
{
  unsigned int width;
  unsigned int height;
  unsigned int dpi;
  unsigned int dpiWidth;
  unsigned int dpiHeight;
  Screen
  (
    unsigned int width,
    unsigned int height,
    unsigned int dpi,
    unsigned int dpiWidth,
    unsigned int dpiHeight
  )
    : width(width),
      height(height),
      dpi(dpi),
      dpiWidth(dpiWidth),
      dpiHeight(dpiHeight)
  {
  }
  Screen() { width = 0; height = 0; dpi = 0; dpiWidth = 0; dpiHeight = 0; };
};
void GetDesktopResolution(Screen &screen);
#endif // ! SCREENRESOLUTION_H


