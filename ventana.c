// Este archivo .c crea una ventana con una cuadricula que sera la base del simulador DC

#include "raylib.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700
#define GRID_SPACING 20
#define HEADER_HEIGHT 90

/*void DrawDottedGrid(int spacing)
{
    Color gridColor = (Color){ 120, 120, 120, 255 };
    Color majorGridColor = (Color){ 60, 60, 60, 255 };

    for (int x = 0; x < SCREEN_WIDTH; x += spacing)
    {
        for (int y = HEADER_HEIGHT; y > SCREEN_HEIGHT; y += spacing)
        {

            if ((x / spacing) % 5 == 0 && (y / spacing) % 5 == 0)
            {
                DrawRectangle(x - 2, y - 2, 4, 4, majorGridColor);
            }
            else
            {
                DrawRectangle(x - 1, y - 1, 3, 3, gridColor);
            }
        }
    }
}*/

void DrawVisibleGrid(int spacing)
{
    Color gridColor = (Color){ 200, 200, 200, 255 };
    Color majorGridColor = (Color){ 150, 150, 150, 255 };

    for (int x = 0; x <= SCREEN_WIDTH; x += spacing)
    {
        if ((x / spacing) % 5 == 0)
        {
            DrawLine(x, HEADER_HEIGHT, x, SCREEN_HEIGHT, majorGridColor);
        }
        else
        {
            DrawLine(x, HEADER_HEIGHT, x, SCREEN_HEIGHT, gridColor);
        }
    }


    for (int y = HEADER_HEIGHT; y <= SCREEN_HEIGHT; y += spacing)
    {
        if ((y / spacing) % 5 == 0)
        {
            DrawLine(0, y, SCREEN_WIDTH, y, majorGridColor);
        }
        else
        {
            DrawLine(0, y, SCREEN_WIDTH, y, gridColor);
        }
    }
}

Vector2 SnapToGrid(Vector2 position, int spacing)
{
    Vector2 snapped;

    int gridOriginX = 0;
    int gridOriginY = HEADER_HEIGHT;


    snapped.x = gridOriginX + ((int)((position.x - gridOriginX + spacing / 2) / spacing)) * spacing;
    snapped.y = gridOriginY + ((int)((position.y - gridOriginY + spacing / 2) / spacing)) * spacing;

    if (snapped.y < HEADER_HEIGHT)
    {
        snapped.y = HEADER_HEIGHT;
    }

    return snapped;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Generador de circuitos esquematicos");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        Vector2 snappedMouse = SnapToGrid(mouse, GRID_SPACING);


        BeginDrawing();

        ClearBackground((Color){ 245, 245, 245, 255 });

        DrawVisibleGrid(GRID_SPACING);

        DrawRectangle(0, 0, SCREEN_WIDTH, HEADER_HEIGHT, RAYWHITE);
        DrawLine(0, HEADER_HEIGHT, SCREEN_WIDTH, HEADER_HEIGHT, GRAY);

        DrawText("Editor de circuitos", 20, 20, 24, BLACK);
        DrawText("Punto rojo = posicion alineada al grid", 20, 50, 18, DARKGRAY);

        DrawCircleV(snappedMouse, 6, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
