#ifndef COMPONENTES_H
#define COMPONENTES_H

//como se utilizan funciones de ambas se deben incluir tambien en el .h
#include <raylib.h>
#include <stdbool.h>    //como nota esta viene incluida en raylib pero por orden se pone aca

//====== Para los Resistores (COMPONENTES) ======
typedef struct 
{
    Vector2 posicion;
    bool visible;

}Resistor;

//====== Para las Fuentes de Tension (COMPONENTES) ======

//====== Para las Fuentes de Corriente (COMPONENTES) ======

void Dibujar_resistor(Resistor resistor); //por ahora solo esta la funcion de dibujado, esto en caso de que el mouse toque el boton 
#endif