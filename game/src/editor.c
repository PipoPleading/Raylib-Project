#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool pbEditorActive = true;
bool pbEditorIntersect = false;

pbEditorData_t pbEditorData;

Rectangle editorRect;

Vector2 anchor01 = { 792,48 };
Texture2D cursorTexture;


bool EditorBoxActive = true;
float MassMinValue = 0.1f;
float MassMaxValue = 0.1f;
float GravitationValue = 0.0f;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");

    Image image = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    HideCursor();

    pbEditorData.anchor01 = (Vector2){ 792,48 };
    pbEditorData.EditorBoxActive = true;
    pbEditorData.MassMinValue = 1;
    pbEditorData.MassMaxValue = 1;
    pbEditorData.GravitationValue = 2;

    pbEditorData.BodyTypeEditMode = true;
    pbEditorData.BodyTypeActive = 0;
    pbEditorData.DampingValue = 0.0f;
    pbEditorData.GravityScaleValue = 0.0f;

    editorRect = (Rectangle){ pbEditorData.anchor01.x + 0,pbEditorData.anchor01.y + 0, 304, 616 };
}

bool IsMouseHoveringRectangle(Rectangle rect) {
    Vector2 mousePosition = GetMousePosition();
    return (mousePosition.x >= rect.x &&
        mousePosition.x < rect.x + rect.width &&
        mousePosition.y >= rect.y &&
        mousePosition.y < rect.y + rect.height);
}

void UpdateEditor(Vector2 position)
{
    if (IsMouseHoveringRectangle(editorRect)) {
        pbEditorActive = true;
    }
    else {
        pbEditorActive = false;
    }
    pbEditorActive = true;
    pbEditorData.EditorBoxActive = true;
    pbEditorIntersect = CheckCollisionPointRec(position, editorRect);
}

void DrawEditor(Vector2 position)
{
    //if (pbEditorData.BodyTypeEditMode) GuiLock();

    //if (pbEditorData.EditorBoxActive)
    //{
    //    pbEditorData.EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 8, anchor01.y + 0, 248, 400 }, "Editor");
    //    GuiGroupBox((Rectangle) {  pbEditorData.anchor01.x + 16, anchor01.y + 40, 232, 224 }, "Body");
    //    GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 104, anchor01.y + 128, 120, 16 }, "Mass Min", NULL, & pbEditorData.MassMinValue, 0, 10);
    //    GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 104, anchor01.y + 160, 120, 16 }, "Mass Max", NULL, & pbEditorData.MassMaxValue, 0, 10);
    //    GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 104, anchor01.y + 192, 120, 16 }, "Damping", NULL, & pbEditorData.DampingValue, 0, 100);
    //    GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 104, anchor01.y + 216, 120, 16 }, "GravityScale", NULL, & pbEditorData.GravityScaleValue, 0, 100);
    //    GuiGroupBox((Rectangle) {  pbEditorData.anchor01.x + 16, anchor01.y + 272, 232, 112 }, "World");
    //    GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 96, anchor01.y + 296, 120, 16 }, "Gravitation", NULL, & pbEditorData.GravitationValue, 0, 100);
    //    //if (GuiDropdownBox((Rectangle) { anchor01.x + 48, anchor01.y + 64, 184, 40 }, "DYNAMIC,KINEMATIC,STATIC", & DropdownBox001Active, DropdownBox001EditMode)) DropdownBox001EditMode = !DropdownBox001EditMode;

    //}
    ////cursor draw
    //DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, WHITE);

    //GuiUnlock();

    if (pbEditorData.BodyTypeEditMode) GuiLock();

    if (pbEditorData.EditorBoxActive) {
        pbEditorData.EditorBoxActive = !GuiWindowBox((Rectangle) { pbEditorData.anchor01.x + 8, pbEditorData.anchor01.y + 32, 248, 400 }, "EDITOR");
            GuiGroupBox((Rectangle) {  pbEditorData.anchor01.x + 16, anchor01.y + 40, 232, 224 }, "Body");
            GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 104, anchor01.y + 128, 120, 16 }, "Mass Min", NULL, & pbEditorData.MassMinValue, 0, 10);
            GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 104, anchor01.y + 160, 120, 16 }, "Mass Max", NULL, & pbEditorData.MassMaxValue, 0, 10);
            GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 104, anchor01.y + 192, 120, 16 }, "Damping", NULL, & pbEditorData.DampingValue, 0, 100);
            GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 104, anchor01.y + 216, 120, 16 }, "GravityScale", NULL, & pbEditorData.GravityScaleValue, 0, 100);
            GuiGroupBox((Rectangle) {  pbEditorData.anchor01.x + 16, anchor01.y + 272, 232, 112 }, "World");
            GuiSliderBar((Rectangle) { pbEditorData.anchor01.x + 96, anchor01.y + 296, 120, 16 }, "Gravitation", NULL, & pbEditorData.GravitationValue, 0, 100);

        if (GuiDropdownBox((Rectangle) { anchor01.x -750, anchor01.y + 64, 184, 40 }, "BT_STATIC;BT_KINEMATIC;BT_DYNAMIC", & pbEditorData.BodyTypeActive, pbEditorData.BodyTypeEditMode)) pbEditorData.BodyTypeEditMode = !pbEditorData.BodyTypeEditMode;
    }
    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, WHITE);
    //
    GuiUnlock();
}

pbBody* GetBodyIntersect(pbBody* bodies, Vector2 position)
{
    for (pbBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass)))
        {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(pbBody* body, Vector2 position)
{
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}