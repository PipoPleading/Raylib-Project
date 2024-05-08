#pragma once
#include "raylib.h"

extern bool pbEditorActive;
extern bool pbEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor();