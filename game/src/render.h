#pragma once
#include "raylib.h"
#include "raymath.h"

extern Vector2 pbScreenSize;
extern float pbScreenZoom;
extern float pbViewSize;

Vector2 ConvertScreenToWorld(Vector2 screen);
Vector2 ConvertWorldToScreen(Vector2 world);
float ConvertWorldToPixel(float world);
