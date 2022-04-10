//====================================================
//
// program name   : ESPDisplay.hpp
// date/author    : 2022/04/08  @chrmlinux03
// update/author  : 2022/04/09  @chrmlinux03
// version        : 0.0.1
// License        : MIT
// --------------------------------------------------
//
//  ESP_8_BIT_composite:
//  Roger Cheng (https://github.com/Roger-random/ESP_8_BIT_composite)
//	MIT
//
//  LovyanGFX:
//  FreeBSD
//  Copyright (c) 2020 lovyan03 (https://github.com/lovyan03)
//
//
//====================================================

#ifndef _ESPDISPLAY_HPP_
#define _ESPDISPLAY_HPP_

#include "Arduino.h"

#define VIDEO_WIDTH  (256)
#define VIDEO_HEIGHT (240)

#include "C_ESP_8_BIT_composite.h"
ESP_8_BIT_composite video(true);

#include "LovyanGFX.hpp"
static LGFX_Sprite lcd;
enum {ESPD_DAC1 = 1, ESPD_DAC2};

class ESPDisp {

  public:

    uint16_t begin(uint16_t);
    uint16_t end(void);
    uint16_t width(void);
    uint16_t height(void);
		uint16_t update(void);
    uint32_t getfps(void);

  private:

    uint32_t _height;
    uint32_t _width;
    uint32_t _size;
		uint8_t *_ary;
    uint16_t _ch;

};

uint32_t ESPDisp::getfps(void)
{
  static uint32_t psec = 0;
  static uint32_t cnt = 0;
  static uint32_t fps = 0;
  uint32_t sec = 0;

  sec = millis() / 1000;
  ++cnt;
  if (psec != sec) {
    psec = sec;
    fps = cnt;
    cnt = 0;
  }
  return fps;
}

uint16_t ESPDisp::begin(uint16_t ch)
{
  uint16_t rtn = 0;
  _height = VIDEO_HEIGHT;
  _width  = VIDEO_WIDTH;
  _size = (_height * _width);
  _ch = ch;

  lcd.setColorDepth(8);
  lcd.createSprite(VIDEO_WIDTH, VIDEO_HEIGHT);
  video.begin((dac_channel_t)_ch);
  return rtn;
}

uint16_t ESPDisp::update(void) 
{
  uint16_t rtn = 0;
  uint8_t *buf = (uint8_t *)lcd.getBuffer();
  uint8_t **vbuf = video.getFrameBufferLines();
  int spos = 0;
  for (int i = 0; i < VIDEO_HEIGHT; i++) {
    memcpy(&vbuf[i][0], &buf[spos], VIDEO_WIDTH);
    spos += VIDEO_WIDTH;
  }
  video.waitForFrame();
  return rtn;
}

uint16_t ESPDisp::end(void)
{
  uint16_t rtn = 0;
  return rtn;
}

uint16_t ESPDisp::width(void)
{
  return _width;
}

uint16_t ESPDisp::height(void)
{
  return _height;
}

#endif
