#include "raylib.h"
#include <stdio.h>

#define ANCHO 1400
#define ALTO 1000
#define ALTURA_TOOLBAR 150


int main (void){

    InitWindow(ANCHO, ALTO, "Ejemplo completo de Raylib"); 
    SetTargetFPS(60); 
    
    while (!WindowShouldClose()){


        BeginDrawing(); 

        ClearBackground(RAYWHITE); 
        DrawText("Hola RAYLIB!", (ANCHO / 2) - 50, (ALTO / 2), 20, BLACK);
        DrawRectangle(0,0,ANCHO,ALTURA_TOOLBAR,LIGHTGRAY);
        DrawRectangleLines(0,0,ANCHO,ALTURA_TOOLBAR,BLACK);
        DrawText("ToolBar",(ANCHO / 2) - 50, 25, 20, BLACK );


        

        EndDrawing(); 
    }


    return 0; 
}

