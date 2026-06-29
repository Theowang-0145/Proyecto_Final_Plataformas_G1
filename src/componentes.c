#include "componentes.h"

//====== Para los Resistores (COMPONENTES) ======

void Dibujar_resistor(Resistor resistor)    //esta funcion recibe el struct planteado anteriormente en los 
{
    int x = resistor.posicion.x;
    int y = resistor.posicion.y;

    //esto es para el dibujo del resistor
    //primero la linea izquierda
    DrawLine(x - 60, y, x - 30, y, BLACK);

    //este es el cuadrado de en medio (Recordar que el eje x crece hacia la derecha pero y hacia abajo. Raylib dibuja del punto hacia la derehca y hacia abajo)
    DrawRectangleLines(x - 30, y - 15, 60, 30, BLACK);

    //esta es la linea derecha
    DrawLine(x + 30, y, x + 60, y, BLACK);



    //esto es para el texto dentro del cuadrado
    DrawText("R1", x - 12, y - 45, 20, BLACK);
    DrawText("1k", x - 12, y + 25, 18, RED);
}

//====== Para las Fuentes de Tension (COMPONENTES) ======

//====== Para las Fuentes de Corriente (COMPONENTES) ======