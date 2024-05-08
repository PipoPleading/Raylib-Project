#include "render.h"  
#include "raymath.h" 

// Default screen size
Vector2 pbScreenSize = { 1280, 720 }; // Screen size width and height

// Default screen zoom level
float pbScreenZoom = 1.0f; // Zoom level of the screen

// Default view size (in world units)
float pbViewSize = 25.0f; // Size of the visible area in the world

// Function to convert screen coordinates to world coordinates
Vector2 ConvertScreenToWorld(Vector2 screen)
{
    // Calculate the aspect ratio of the screen
    float ratio = pbScreenSize.x / pbScreenSize.y;

    // Calculate the extents of the visible area in the world
    Vector2 extents = (Vector2){ pbViewSize * ratio, pbViewSize };
    extents = Vector2Scale(extents, pbScreenZoom);

    // Calculate the lower and upper bounds of the visible area
    Vector2 lower = Vector2Negate(extents);
    Vector2 upper = extents;

    // Normalize the screen coordinates
    float nx = screen.x / pbScreenSize.x;
    float ny = (pbScreenSize.y - screen.y) / pbScreenSize.y;

    // Convert normalized screen coordinates to world coordinates
    Vector2 world;
    world.x = ((1 - nx) * lower.x) + (nx * upper.x);
    world.y = ((1 - ny) * lower.y) + (ny * upper.y);

    return world;
}

// Function to convert world coordinates to screen coordinates
Vector2 ConvertWorldToScreen(Vector2 world)
{
    // Calculate the aspect ratio of the screen
    float ratio = pbScreenSize.x / pbScreenSize.y;

    // Calculate the extents of the visible area in the world
    Vector2 extents = (Vector2){ pbViewSize * ratio, pbViewSize };
    extents = Vector2Scale(extents, pbScreenZoom);

    // Calculate the lower and upper bounds of the visible area
    Vector2 lower = Vector2Negate(extents);
    Vector2 upper = extents;

    // Normalize the world coordinates
    float nx = (world.x - lower.x) / (upper.x - lower.x);
    float ny = (world.y - lower.y) / (upper.y - lower.y);

    // Convert normalized world coordinates to screen coordinates
    Vector2 screen;
    screen.x = nx * pbScreenSize.x;
    screen.y = (1.0f - ny) * pbScreenSize.y;

    return screen;
}

// Function to convert world units to pixel units
float ConvertWorldToPixel(float world)
{
    // Calculate the aspect ratio of the screen
    float ratio = pbScreenSize.x / pbScreenSize.y;

    // Calculate the extents of the visible area in the world
    Vector2 extents = (Vector2){ pbViewSize * ratio, pbViewSize };
    extents = Vector2Scale(extents, pbScreenZoom);

    // Normalize the world value
    float nx = world / extents.x;

    // Convert normalized world value to pixel value
    float pixel = nx * pbScreenSize.x;

    return pixel;
}
