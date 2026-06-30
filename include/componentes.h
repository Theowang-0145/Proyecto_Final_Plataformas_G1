#ifndef COMPONENTES_H
#define COMPONENTES_H

//como se utilizan funciones de ambas se deben incluir tambien en el .h
#include <raylib.h>
#include <stdbool.h>    //como nota esta viene incluida en raylib pero por orden se pone aca
#include <stdlib.h>

//====== Para los Resistores (COMPONENTES) ======
typedef struct 
{
    Vector2 posicion;
    bool visible;
    bool seleccionado;

}Resistor;

typedef struct 
{
    Resistor *resistores; //aca se encuentran practicamente todos los resistores almacenados
    size_t tamano; 
    size_t capacidad; 
}ArregloResistores;

void InicializarArreglo_Res(ArregloResistores *punt_datos, size_t capacidad_inicial);
void Anadir_Resistor(ArregloResistores *punt_datos);
void Dibujar_resistor(ArregloResistores *punt_datos); //por ahora solo esta la funcion de dibujado, esto en caso de que el mouse toque el boton 
void Liberar_Arreglo_Resistores(ArregloResistores *punt_datos);


//====== Para las Fuentes de Tension (COMPONENTES) ======

//====== Para las Fuentes de Corriente (COMPONENTES) ======


#endif