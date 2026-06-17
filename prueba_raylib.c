/*
Este es un archivo de pureba de que a todos nos compila el raylib y demas. Compilen este con este comando:
gcc <nombre de la prueba>.c -o prueba -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lXi -lXrandr -lXinerama -lXcursor

ya cuando hagamos el makefile podemos meter todas esas librerias ahi y ya compila mas facilito. por ahora se ve asi
*/



#include "raylib.h"

int main(void)
{
    InitWindow(800, 400, "Ventana de prueba");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Hola RAYLIB!", 300, 200, 20, BLACK);
        DrawCircle(100, 300, 5.0, RED);
        DrawCircle(700, 100, 10.0, BLUE);
        DrawCircle(700, 200, 30.0, GREEN);
        DrawCircle(100, 50, 50.0, GRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}