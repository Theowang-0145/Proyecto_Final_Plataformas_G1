#include "raylib.h"
#include <stdio.h>

//estas son varias constantes importantes que se van a usar siempre. 
#define ANCHO 1400
#define ALTO 1000
#define ALTURA_TOOLBAR 150
#define ESPACIADO_GRID 20

//OJO se utillizan structs para los resistores, USAR ESTA MISMA ESTRUCTURA PARA LOS DEMAS COMPONENTES
typedef struct 
{
    //tentativamente vendrian dos variables mas que serian float de valor y cont char de texto, inclusive podriamos hacer un boton de editar despues para no complicarnos
    Vector2 posicion; 
    bool visible;
    //float valor
    //char const nombre  
} Resistor;

//esta funcion es muy general, se puede usar para todas pues es para botones y de tipo bool para la funcion de boton
bool ButtonClicked(Rectangle boton)
{
    Vector2 mouse = GetMousePosition();

    return CheckCollisionPointRec(mouse, boton) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

//esto es muy de dibujo, USAR ESTA MISMA ESTRUCTURA PARA LOS DEMAS COMPONENTES
void dibujar_resistor(Resistor resistor){

    int x = resistor.posicion.x; 
    int y = resistor.posicion.y; 

    //PARA TERMINOS DE FACILIDAD PONEMOS INCLUIR CUADRADOS EN CADA TERMINAL PARA QUE SIRVA COMO PUNTO DE CONEXCION MANUAL (SE PREGUNTA A QUE NODO CONECTAR)
    DrawLine(x - 60, y, x - 30, y, BLACK);
    DrawRectangleLines(x - 30, y - 15, 60, 30, BLACK);
    DrawLine(x + 30, y, x + 60, y, BLACK);

    // estas nombres se pueden cambiar, se podrian poner por default pero dejarlas como variables en terminos de interaccion
    //mantener las dimensiones del rectagulo, son correctas y se ven de buen tamano

    DrawText("R1", x - 12, y - 45, 20, BLACK);
    DrawText("1k", x - 12, y + 25, 18, RED);
}


//USAR ESTA MISMA ESTRUCTURA PARA TODOS LOS BOTONES
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


//esta funcion es de solo poner una vez, TAL VEZ SE PUEDE CAMBIAR EL COLOR PARA QUE HAGA MAS CONTRASTE CON LOS COMPONENTES
void Imprimir_Grid(){

    Color gridColor = (Color){ 200, 200, 200, 255 };
    Color majorGridColor = (Color){ 150, 150, 150, 255 };


    //TOMAR EN CUENTA QUE EL GRID DEPENDE DE LOS DEFINE DE ANTES ENTONCES TENER CUIDADO CON TODO ESO


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


    //se inicialiaz simepre primero
    InitWindow(ANCHO, ALTO, "Ejemplo completo de Raylib"); 
    SetTargetFPS(60); 

    //se inixializa una variable resistor inicial donde e van a pegar todas las resistencias
    Resistor resistor = {
        .posicion = {500, 500},
        .visible = false
        //float default
        //char default
    };
    
    while (!WindowShouldClose()){


        BeginDrawing(); 

        ClearBackground(RAYWHITE); 


        DrawRectangle(0,0,ANCHO,ALTURA_TOOLBAR,LIGHTGRAY);
        DrawRectangleLines(0,0,ANCHO,ALTURA_TOOLBAR,BLACK);
        DrawText("Barra de herramientas",(ANCHO / 2) - 100, 25, 20, BLACK );


        Imprimir_Grid(); 

        //LLAMADO DE BOTONES ACA IMPLEMENTAR MAS
        Rectangle resistor_boton = {20, 20, 180, 45};
        dibujar_boton(resistor_boton, "Agregar R");

        //HACER ESTO MISMO PARA TODOS LOS BOTONES QUE HAYA
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

