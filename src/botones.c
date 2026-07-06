#include "botones.h"

//esta es la funcion del booleano que retorna un true si el boton es clickeado
bool ButtonClicked(Rectangle boton) //recibe el boton a analizar si esta clickeado o no

{
    bool click;
    bool encima;

    //se obtiene el vector del mouse o su posicion para las interacciones con las cosas
    Vector2 mouse = GetMousePosition();

    encima = CheckCollisionPointRec(mouse,boton);   //ambas funciones de raylib retornan booleanos
    click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);    //una recibe si esta sobre el objeto, la otra recibe si esta siendo clickeado

    if ((encima == true) && (click == true)){
        return true;
    }
    return false;
}


//esta es la funcion para dibujar el boton de un componente (recordar que se uso un struct de raylib especifico para botones)
void Dibujar_boton(Rectangle boton_general, const char* texto)
{
    
    Vector2 mouse = GetMousePosition();

    //este condicional se utiliza para cambiar el color del texto cuando el puntero del mouse se encuentre sobre el boton
    if (CheckCollisionPointRec(mouse, boton_general))
    {
        //esta funcion dibuja el boton perce, sin bordes que resalten pero de otro color
        DrawRectangleRec(boton_general, LIGHTGRAY);
    }
    else
    {
        //al igual que esta pero de otro color
        DrawRectangleRec(boton_general, GRAY);
    }

    //esta funcion dibuja las lineas del rectangulo dle boton para que resalten sobre este mismo
    DrawRectangleLines(boton_general.x,boton_general.y,boton_general.width,boton_general.height,BLACK);

    //el texto igual se coloca dentro del boton jugando con las coordenadas y la propia funcion de raylib. Ver que recibe un char de texto
    DrawText(texto, boton_general.x + 15, boton_general.y + 12, 20, BLACK);
}