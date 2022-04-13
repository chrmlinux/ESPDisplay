//====================================================
//
// program name   : spriteSample.hpp
// date/author    : 2021/12/05  @chrmlinux03
// update/author  : 2022/04/10  @chrmlinux03
// version        : 0.0.1
// License        : MIT
// https://qiita.com/chrmlinux03/items/c66ca9ff5abcc9560902
// --------------------------------------------------
//  ESP_8_BIT_composite:
//  Roger Cheng (https://github.com/Roger-random/ESP_8_BIT_composite)
//  MIT
// --------------------------------------------------
//  LovyanGFX:
//  FreeBSD
//  Copyright (c) 2020 lovyan03 (https://github.com/lovyan03)
//====================================================

#include <ESPDisplay.hpp>
#include "img.h"
static LGFX_Sprite spr;
static ESPDisp espd;

void setup()
{
  espd.begin(ESPD_DAC1);
  spr.setColorDepth(8);
  spr.createSprite(imgWidth, imgHeight);
  spr.setPivot(spr.width() / 2, spr.height() /2);
  spr.pushImage(0, 0, spr.width(), spr.height(), img);
}

void loop()
{
  espd.update();
  
  static float zm = 0.5;
  static float zmstp = 0.025;
  static uint16_t r = 0;
  static int rstp = 4;
  static int xstp = 2;
  static int ystp = 2;
  static uint16_t x = lcd.width() / 2;
  static uint16_t y = lcd.height() / 2;
  x += xstp; if (((x - (spr.width () * zm)) < 0) || ((x + (spr.width () * zm))>  VIDEO_WIDTH)) xstp = -xstp;
  y += ystp; if (((y - (spr.width () * zm)) < 0) || ((y + (spr.height() * zm))> VIDEO_HEIGHT)) ystp = -ystp;
  r += rstp; if ((r < 0) || (r > 360)) rstp = -rstp;
  zm += zmstp; if ((zm < 0.3) || (zm > 3.14)) zmstp = -zmstp;

//  lcd.startWrite();
//  lcd.clear(TFT_BLACK);
  spr.pushRotateZoom(&lcd, x, y, r, zm, zm, TFT_BLACK);
  lcd.setCursor(8, VIDEO_HEIGHT - 16);
  lcd.print(espd.getfps());
  lcd.print("fps Thx.LovyanGFX/ESP_8_BIT_composite");
//  lcd.endWrite();
}
