#include "raylib.h"
#include <stdio.h>

#define ANCHO 1400
#define ALTO 1000
#define ALTURA_TOOLBAR 150
#define ESPACIADO_GRID 20


typedef struct 
{
    Vector2 posicion; 
    bool visible;
} Resistor;

bool ButtonClicked(Rectangle boton)
{
    Vector2 mouse = GetMousePosition();

    return CheckCollisionPointRec(mouse, boton) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void dibujar_resistor(Resistor resistor){

    int x = resistor.posicion.x; 
    int y = resistor.posicion.y; 

    DrawLine(x - 60, y, x - 30, y, BLACK);
    DrawRectangleLines(x - 30, y - 15, 60, 30, BLACK);
    DrawLine(x + 30, y, x + 60, y, BLACK);

    DrawText("R1", x - 12, y - 45, 20, BLACK);
    DrawText("1k", x - 12, y + 25, 18, RED);
}


void dibujar_boton(Rectangle boton_general, const char* texto){

    Vector2 mouse = GetMousePosition(); 

    if (CheckCollisionPointRec(mouse,boton_general)){
        DrawRectangleRec(boton_general,LIGHTGRAY);  
    }
    else {
        DrawRectangleRec(boton_general,GRAY);
    }

    DrawRectangleLines(boton_general.x, boton_general.y, boton_general.width, boton_general.height, BLACK);
    DrawText(texto, boton_general.x + 15, boton_general.y + 12, 20, BLACK);
}

void Imprimir_Grid(){

    Color gridColor = (Color){ 200, 200, 200, 255 };
    Color majorGridColor = (Color){ 150, 150, 150, 255 };

    for (int x = 0; x <= ANCHO; x += ESPACIADO_GRID)
    {
        if ((x / ESPACIADO_GRID) % 5 == 0)
        {
            DrawLine(x, ALTURA_TOOLBAR, x, ALTO, majorGridColor);
        }
        else
        {
            DrawLine(x, ALTURA_TOOLBAR, x, ALTO, gridColor);
        }
    }


    for (int y = ALTURA_TOOLBAR; y <= ALTO; y += ESPACIADO_GRID)
    {
        if ((y / ESPACIADO_GRID) % 5 == 0)
        {
            DrawLine(0, y, ANCHO, y, majorGridColor);
        }
        else
        {
            DrawLine(0, y, ANCHO, y, gridColor);
        }
    }
}


int main (void){

    InitWindow(ANCHO, ALTO, "Ejemplo completo de Raylib"); 
    SetTargetFPS(60); 

    Resistor resistor = {
        .posicion = {500, 500},
        .visible = false
    };
    
    while (!WindowShouldClose()){


        BeginDrawing(); 

        ClearBackground(RAYWHITE); 
        //DrawText("Hola RAYLIB!", (ANCHO / 2) - 50, (ALTO / 2), 20, BLACK);
        DrawRectangle(0,0,ANCHO,ALTURA_TOOLBAR,LIGHTGRAY);
        DrawRectangleLines(0,0,ANCHO,ALTURA_TOOLBAR,BLACK);
        DrawText("Barra de herramientas",(ANCHO / 2) - 100, 25, 20, BLACK );
        Imprimir_Grid(); 

        Rectangle resistor_boton = {20, 20, 180, 45};
        dibujar_boton(resistor_boton, "Agregar R");


        if(ButtonClicked(resistor_boton)){
            resistor.visible = true;
        }

        if(resistor.visible){
            dibujar_resistor(resistor);
        }

        EndDrawing(); 
    }
    return 0; 
}

