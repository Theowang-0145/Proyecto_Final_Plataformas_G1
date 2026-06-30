#ifndef COMPONENTES_H
#define COMPONENTES_H

//como se utilizan funciones de ambas se deben incluir tambien en el .h
#include <raylib.h>
#include <stdbool.h>    //como nota esta viene incluida en raylib pero por orden se pone aca
#include <stdlib.h>

//====== Para los Resistores (COMPONENTES) ======
typedef struct 
{
    Vector2 posicion;   //luego hay que implementarlo al snap to grid
    bool visible;
    bool seleccionado;  //este bool luego hay que trabajarlo para poder seleccionar y mover

}Resistor;

//esto de aca ya no se toca (por ahora jeje creo que si para el snap y el seleccionado pero asi se ve bien)
typedef struct 
{
    Resistor *resistores; //aca se encuentran practicamente todos los resistores almacenados
    size_t tamano; 
    size_t capacidad; 
}ArregloResistores;

void InicializarArreglo_Res(ArregloResistores *punt_datos, size_t capacidad_inicial);  //inicializa el arreglo (Como el lab 5)
void Anadir_Resistor(ArregloResistores *punt_datos);//anade resistores (como el lab 5)
void Dibujar_resistor(ArregloResistores *punt_datos); //los dibuja, pero sus posiciones son variables de structs (Como el lab 5)
void Liberar_Arreglo_Resistores(ArregloResistores *punt_datos);//libera la mmoria (igual que el lab 5)

void Seleccion_movimiento_resistores(ArregloResistores *punt_datos);
Rectangle Caja_de_seleccion_resistor(Resistor resistor); 


//====== Para las Fuentes de Tension (COMPONENTES) ======

//====== Para las Fuentes de Corriente (COMPONENTES) ======


#endif