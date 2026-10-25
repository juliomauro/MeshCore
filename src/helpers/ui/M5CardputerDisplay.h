#pragma once

#include <M5Cardputer.h>
#include "DisplayDriver.h"

// M5Cardputer uses standard color constants
#ifndef TFT_BLACK
#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF
#define TFT_RED 0xF800
#define TFT_GREEN 0x07E0
#define TFT_BLUE 0x001F
#define TFT_YELLOW 0xFFE0
#define TFT_ORANGE 0xFD20
#define TFT_CYAN 0x07FF
#endif

class M5CardputerDisplay : public DisplayDriver {
private:
  bool _isOn = false;
  uint16_t cursor_x = 0;
  uint16_t cursor_y = 0;
  uint16_t text_size = 1;
  ColorVal _color = TFT_WHITE;
  static const uint16_t SCREEN_WIDTH = 240;
  static const uint16_t SCREEN_HEIGHT = 135;
  static const uint8_t CHAR_WIDTH = 6;
  static const uint8_t CHAR_HEIGHT = 8;

public:
  M5CardputerDisplay() : DisplayDriver(SCREEN_WIDTH, SCREEN_HEIGHT) {}

  bool begin() {
    _isOn = true;
    M5.Display.setRotation(1);  // Landscape orientation
    M5.Display.fillScreen(TFT_BLACK);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Display.setTextSize(1);
    Serial.println("M5Cardputer Display initialized");
    return true;
  }

  bool isOn() override { return _isOn; }

  void turnOn() override {
    if (!_isOn) {
      M5.Display.wakeup();
      _isOn = true;
    }
  }

  void turnOff() override {
    if (_isOn) {
      M5.Display.sleep();
      _isOn = false;
    }
  }

  void startFrame(ColorVal bkg = UIColor::window_bkg) override {
    if (!_isOn) return;
    M5.Display.fillScreen(bkg);
    cursor_x = 0;
    cursor_y = 0;
  }

  void endFrame() override {
    if (!_isOn) return;
    // No buffering, changes are immediate
  }

  void clear() override {
    if (!_isOn) return;
    M5.Display.fillScreen(TFT_BLACK);
    cursor_x = 0;
    cursor_y = 0;
  }

  void setCursor(int x, int y) override {
    cursor_x = x;
    cursor_y = y;
    M5.Display.setCursor(x, y);
  }

  void setTextSize(int sz) override {
    text_size = sz;
    M5.Display.setTextSize(sz);
  }

  void setColor(ColorVal c) override {
    _color = c;
    M5.Display.setTextColor(_color, TFT_BLACK);
  }

  void print(const char* str) override {
    if (!_isOn) return;
    M5.Display.print(str);
  }

  void drawRect(int x, int y, int w, int h) override {
    if (!_isOn) return;
    M5.Display.drawRect(x, y, w, h, _color);
  }

  void fillRect(int x, int y, int w, int h) override {
    if (!_isOn) return;
    M5.Display.fillRect(x, y, w, h, _color);
  }

  void drawXbm(int x, int y, const uint8_t* bits, int w, int h) override {
    if (!_isOn) return;
    // XBM drawing - simplified implementation
    for (int yy = 0; yy < h; yy++) {
      for (int xx = 0; xx < w; xx++) {
        int byte_idx = (yy * ((w + 7) / 8)) + (xx / 8);
        int bit_idx = xx % 8;
        if (bits[byte_idx] & (1 << bit_idx)) {
          M5.Display.drawPixel(x + xx, y + yy, _color);
        }
      }
    }
  }

  uint16_t getTextWidth(const char* str) override {
    return strlen(str) * CHAR_WIDTH * text_size;
  }

};

// Helper inline for text drawing
inline void drawTextLine(M5CardputerDisplay& disp, int y, const char* str) {
  disp.setCursor(0, y);
  disp.print(str);
}
