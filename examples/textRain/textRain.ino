//====================================================
//
// program name   : textRain.ino
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
#include "ESPDisplay.hpp"
static ESPDisp espd;
static LGFX_Sprite spr;

//====================================================
//
// textRain:
// https://qiita.com/chrmlinux03/items/c8668f2447dd61a6aabb
//
//====================================================
void px(int x, int y, int h, int c) {
  spr.setTextColor(lcd.color888(0, c, 0));
  spr.setCursor(x * h, y * h);
  spr.printf("%c", random(0x21, 0x7e));
}
void textRain(int x, int y, int h) {
  static int yp[40] = {1};
  for (int i = 0; i < x; i++) {
    px(i, yp[i], h, 0xff);
    int p = 0;
    for (int j = yp[i] - y; j < yp[i]; j++) {
      px(i, j, h, (p << 3));
      p++;
    }
    if (yp[i] > y) {
      if (random(1000) > 975) yp[i] = 0;
    }
    yp[i]++;
  }
}

//====================================================
//
// setup
//
//====================================================
void setup()
{

  espd.begin(ESPD_DAC1);
  //  espd.begin(ESPD_DAC2);

  spr.setColorDepth(8);
  spr.createSprite(VIDEO_WIDTH, VIDEO_HEIGHT);
  spr.setPivot(VIDEO_WIDTH / 2, VIDEO_HEIGHT / 2);
}

//====================================================
//
// loop
//
//====================================================
void loop()
{
  static int r = 0;
  static int stp = 1;
  static float zm = 1.0;
  static float zstp = 0.01;

  lcd.startWrite();
  spr.clear(TFT_BLACK);
  lcd.clear(TFT_BLACK);
  uint16_t tsz = 8; textRain(VIDEO_WIDTH / tsz, VIDEO_HEIGHT / tsz, tsz);
  spr.pushRotateZoom(&lcd, VIDEO_WIDTH / 2, VIDEO_HEIGHT / 2, r, zm, zm);
  lcd.setCursor(lcd.width() / 2, lcd.height() / 2);
  lcd.print(espd.getfps()); lcd.print("fps");
  lcd.endWrite();

  espd.update();

  r += stp; if ((r < 0) || (r > (360 - 1))) stp = -stp;
  zm += zstp; if ((zm < 1.0) || (zm > (3.14 - 0.01))) zstp = -zstp;
}
