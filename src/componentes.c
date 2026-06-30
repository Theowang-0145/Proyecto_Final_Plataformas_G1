#include "componentes.h"
#include <stdio.h>
#include <stdlib.h>


//====== Para los Resistores (COMPONENTES) ======

void InicializarArreglo_Res(ArregloResistores *punt_datos, size_t capacidad_inicial){

    punt_datos->resistores = NULL; 
    punt_datos->tamano=0;
    punt_datos->capacidad=0;

    punt_datos->resistores = malloc(capacidad_inicial * sizeof(Resistor)); 

    if (punt_datos->resistores == NULL){
        printf("\n ERROR NO SE LOGRO GUARDAR MEMORIA PARA EL ARREGLO DINAMICO");
        return;
    }

    punt_datos->capacidad = capacidad_inicial; 
}

void Anadir_Resistor(ArregloResistores *punt_datos){

    Resistor resistor = {
        .posicion = {(500 + (punt_datos->tamano*5 + 10) ) , (500 + (punt_datos->tamano*5 + 10) )},
        .visible = false,
        .seleccionado = false
    };

    if (punt_datos->tamano == punt_datos->capacidad){

        size_t nueva_capacidad = punt_datos->capacidad * 2;

        Resistor *nuevo = realloc(punt_datos->resistores, nueva_capacidad * sizeof(Resistor));

        if (nuevo == NULL){
            printf("NO SE PUDO GENERAR NUEVA MEMORIA PARA EL ARREGLO DE RESISTORES");
            return;
        }

        punt_datos->resistores = nuevo; 
        punt_datos->capacidad = nueva_capacidad;

    }

    punt_datos->resistores[punt_datos->tamano] = resistor; 
    punt_datos->resistores[punt_datos->tamano].visible = true;
    punt_datos->tamano ++; 

}
void Dibujar_resistor(ArregloResistores *punt_datos)    //esta funcion recibe el struct planteado anteriormente en los 
{
    for (size_t i = 0; i < punt_datos->tamano; i ++ ){

        int x = punt_datos->resistores[i].posicion.x;
        int y = punt_datos->resistores[i].posicion.y;

        DrawLine(x - 60, y, x - 30, y, BLACK);

    //este es el cuadrado de en medio (Recordar que el eje x crece hacia la derecha pero y hacia abajo. Raylib dibuja del punto hacia la derehca y hacia abajo)
        DrawRectangleLines(x - 30, y - 15, 60, 30, BLACK);

    //esta es la linea derecha
        DrawLine(x + 30, y, x + 60, y, BLACK);



    //esto es para el texto dentro del cuadrado
        DrawText("R", x - 12, y - 45, 20, BLACK);
        DrawText("1k", x - 12, y + 25, 18, RED);

    }
}

void Liberar_Arreglo_Resistores(ArregloResistores *punt_datos){

        if (punt_datos->resistores != NULL)
    {
        free(punt_datos->resistores);

        punt_datos->resistores = NULL;
        punt_datos->tamano = 0;
        punt_datos->capacidad = 0;
    }

    punt_datos->resistores = NULL; 
    punt_datos->capacidad = 0; 
    punt_datos->tamano = 0; 
}

//====== Para las Fuentes de Tension (COMPONENTES) ======

//====== Para las Fuentes de Corriente (COMPONENTES) ======