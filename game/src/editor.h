#pragma once
#include "raylib.h"

typedef struct pbEditorData
{
    Vector2 anchor01;

    bool EditorBoxActive;
    float MassMinValue;
    float MassMaxValue;
    float GravitationValue;
    bool BodyTypeEditMode;
    int BodyTypeActive;
    float DampingValue;
    float GravityScaleValue;

} pbEditorData_t;

extern pbEditorData_t pbEditorData;

extern bool pbEditorActive;
extern bool pbEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);

struct pbBody* GetBodyIntersect(struct pbBody* bodies, Vector2 position); 
void DrawLineBodyToPosition(struct pbBody* body, Vector2 position);