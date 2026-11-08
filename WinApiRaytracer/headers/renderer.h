#ifndef RENDERER_H
#define RENDERER_H

#include <Windows.h>
#include <cstdint>
#include "settings.h"
#include "objects.h"

extern HDC Rhdc;
extern uint32_t RPixels[STScreenWidth * STScreenHeight]; 

extern OBJCamera* Camera;
extern OBJSun* Sun;

extern float HPixelStep;
extern float VPixelStep;

extern int xpos;


void RInitRenderer();
void RRenderScreen();
void RWriteToScreen();
void ClearScreen();

void RRenderRect(uint16_t x, uint16_t y, uint16_t sx, uint16_t sy, uint32_t rgb);

#endif