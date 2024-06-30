#ifndef __GAME_H__
#define __GAME_H__

#include <stdint.h>
#include "macros.h"

void start();

IMPORT_FUNC("print")
void println(const char* message);

IMPORT_FUNC("init")
void init();

IMPORT_FUNC("sqrt")
double sqrt(double x);

IMPORT_FUNC("getRandom")
double getRandom();

IMPORT_FUNC("createWindow")
void createWindow(const char* title, int32_t width, int32_t height);

IMPORT_FUNC("runGameLoop")
void runGameLoop(void (*gameLoop)(float), void (*onComplete)());

IMPORT_FUNC("setDrawColor")
void setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

IMPORT_FUNC("clearScreen")
void clearScreen();

IMPORT_FUNC("drawRect")
void drawRect(int32_t x, int32_t y, int32_t width, int32_t height);

IMPORT_FUNC("fillRect")
void fillRect(int32_t x, int32_t y, int32_t width, int32_t height);

IMPORT_FUNC("drawCircle")
void drawCircle(int32_t x, int32_t y, int32_t radius);

IMPORT_FUNC("fillCircle")
void fillCircle(int32_t x, int32_t y, int32_t radius);

IMPORT_FUNC("destroyWindow")
void destroyWindow();

IMPORT_FUNC("quit")
void quit();

IMPORT_FUNC("setOnClick")
void setOnClick(void (*onClick)(int x, int y));

#endif // __GAME_H__
