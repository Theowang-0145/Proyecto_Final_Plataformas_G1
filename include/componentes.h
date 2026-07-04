#ifndef COMPONENTES_H
#define COMPONENTES_H

//como se utilizan funciones de ambas se deben incluir tambien en el .h
#include <raylib.h>
#include <stdbool.h>    //como nota esta viene incluida en raylib pero por orden se pone aca
#include <stdlib.h>

#define MAX_TEXTO_COMPONENTE 20

//====== Para los Resistores (COMPONENTES) ======
typedef struct 
{
    Vector2 posicion;   //luego hay que implementarlo al snap to grid
    bool visible;
    bool seleccionado;  //este bool luego hay que trabajarlo para poder seleccionar y mover
    char nombre[MAX_TEXTO_COMPONENTE];
    char valor[MAX_TEXTO_COMPONENTE];

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
bool Eliminar_Resistor_Seleccionado(ArregloResistores *punt_datos); //elimina el resistor

void Seleccion_movimiento_resistores(ArregloResistores *punt_datos);
Rectangle Caja_de_seleccion_resistor(Resistor resistor); 
void Mover_Resistor(ArregloResistores *punt_datos); 


//====== Para las Fuentes de Tension (COMPONENTES) ======

typedef struct 
{
    Vector2 posicion;   //luego hay que implementarlo al snap to grid
    bool visible;
    bool seleccionado;  //este bool luego hay que trabajarlo para poder seleccionar y mover
    char nombre[MAX_TEXTO_COMPONENTE];
    char valor[MAX_TEXTO_COMPONENTE];
}Fuentes_T;

//esto de aca ya no se toca (por ahora jeje creo que si para el snap y el seleccionado pero asi se ve bien)
typedef struct 
{
    Fuentes_T *fuentes_T; //aca se encuentran practicamente todos los resistores almacenados
    size_t tamano; 
    size_t capacidad; 
}ArregloFuentes_T;

void InicializarArreglo_F_T(ArregloFuentes_T *punt_datos, size_t capacidad_inicial);  //inicializa el arreglo (Como el lab 5)
void Anadir_Fuente_T(ArregloFuentes_T *punt_datos);//anade resistores (como el lab 5)
void Dibujar_Fuente_T(ArregloFuentes_T *punt_datos); //los dibuja, pero sus posiciones son variables de structs (Como el lab 5)
void Liberar_Arreglo_Fuente_T(ArregloFuentes_T *punt_datos);//libera la mmoria (igual que el lab 5)
bool Eliminar_Fuente_T_Seleccionada(ArregloFuentes_T *punt_datos); //elimina la fuente


void Seleccion_movimiento_Fuente_T(ArregloFuentes_T *punt_datos);
Rectangle Caja_de_seleccion_Fuente_T(Fuentes_T fuente_T); 
void Mover_Fuente_T(ArregloFuentes_T *punt_datos); 

//====== Para las Fuentes de Corriente (COMPONENTES) ======

typedef struct 
{
    Vector2 posicion;   //luego hay que implementarlo al snap to grid
    bool visible;
    bool seleccionado;  //este bool luego hay que trabajarlo para poder seleccionar y mover
    char nombre[MAX_TEXTO_COMPONENTE];
    char valor[MAX_TEXTO_COMPONENTE];

}Fuentes_C;

//esto de aca ya no se toca (por ahora jeje creo que si para el snap y el seleccionado pero asi se ve bien)
typedef struct 
{
    Fuentes_C *fuentes_C; //aca se encuentran practicamente todos los resistores almacenados
    size_t tamano; 
    size_t capacidad; 
}ArregloFuentes_C;

void InicializarArreglo_F_C(ArregloFuentes_C *punt_datos, size_t capacidad_inicial);  //inicializa el arreglo (Como el lab 5)
void Anadir_Fuente_C(ArregloFuentes_C *punt_datos);//anade resistores (como el lab 5)
void Dibujar_Fuente_C(ArregloFuentes_C *punt_datos); //los dibuja, pero sus posiciones son variables de structs (Como el lab 5)
void Liberar_Arreglo_Fuente_C(ArregloFuentes_C *punt_datos);//libera la mmoria (igual que el lab 5)
bool Eliminar_Fuente_C_Seleccionada(ArregloFuentes_C *punt_datos); //elimina la fuente de corriente

void Seleccion_movimiento_Fuente_C(ArregloFuentes_C *punt_datos);
Rectangle Caja_de_seleccion_Fuente_C(Fuentes_C fuente_T); 
void Mover_Fuente_C(ArregloFuentes_C *punt_datos); 



//====== Para los nodos (COMPONENTES) ======

typedef struct 
{
    Vector2 posicion;   //luego hay que implementarlo al snap to grid
    bool visible;
    bool seleccionado;  //este bool luego hay que trabajarlo para poder seleccionar y mover
    char nombre[MAX_TEXTO_COMPONENTE];
    char valor[MAX_TEXTO_COMPONENTE];

}Nodo;

//esto de aca ya no se toca (por ahora jeje creo que si para el snap y el seleccionado pero asi se ve bien)
typedef struct 
{
    Nodo *nodo; //aca se encuentran practicamente todos los resistores almacenados
    size_t tamano; 
    size_t capacidad; 
}ArregloNodos;

void InicializarArregloNodo(ArregloNodos *punt_datos, size_t capacidad_inicial);  //inicializa el arreglo (Como el lab 5)
void Anadir_Nodo(ArregloNodos *punt_datos);//anade resistores (como el lab 5)
void Dibujar_Nodo(ArregloNodos *punt_datos); //los dibuja, pero sus posiciones son variables de structs (Como el lab 5)
void Liberar_Arreglo_Nodo(ArregloNodos *punt_datos);//libera la mmoria (igual que el lab 5)
bool Eliminar_Nodo_Seleccionado(ArregloNodos *punt_datos); //elimina el nodo

void Seleccion_movimiento_Nodo(ArregloNodos *punt_datos);
Rectangle Caja_de_seleccion_Nodo(Nodo nodo); 
void Mover_Nodo(ArregloNodos *punt_datos); 

#endif
