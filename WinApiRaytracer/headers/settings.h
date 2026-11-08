#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstdint> // C++ projelerinde stdbool.h/stdint.h yerine cstdint/cstdbool tercih edilir
#include "math.h"

#define HEX_RGB(r, g, b) ((COLORREF)(((BYTE)(b) | ((WORD)((BYTE)(g)) << 8)) | (((DWORD)(BYTE)(r)) << 16)))

// extern kullanarak çoklu tanım (multiple definition) hatasını önlüyoruz
extern bool STisRunning;

constexpr int STScreenWidth = 750;
constexpr int STScreenHeight = 750;
constexpr float STScreenRatio = STScreenWidth / STScreenHeight;

constexpr int OBJPoolSize = 128;

constexpr float STCameraSensitivity = 0.1f;
constexpr float STCameraSpeed = 1.0f;

constexpr float STFOV = 75.0f;

constexpr int STThreadCount = 15;

#endif