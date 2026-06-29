#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "raylib.h"

//variables a utilizar para el grid, el toolbar y la ventan de raylib se pueden cambiar si quieren
#define ANCHO 1400 
#define ALTO 1000
#define ALTURA_TOOLBAR 150
#define ESPACIADO_GRID 20

//-----------modularizacion del proyecto-----------

//aca se incializa unicamente la ventana del simulador
void InicializarSimulador(void);

//este corresponde a una interaccion, por ejemplo si se toca un boton para anadir algun componente
void ActualizarSimulador(void);

//esta funcion dibujo todo el entorno de trabajo, incluyendo botones y el grid
void DibujarSimulador(void);

//esta funcion simplemente cierra la ventana 
void CerrarSimulador(void);

//este funcion se utiliza para imprimir el grid dentro de la funcion de DibujarSimulador
void Imprimir_Grid(void);

#endif