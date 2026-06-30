#include "botones.h"
#include "componentes.h"
#include "simulador.h"

#include <raylib.h>
#include <stdio.h>

//----------Seccion de posicones y dimensiones de componentes(dibujo del componente y su boton asociado)-----------------

//====== Para los Resistores ======

ArregloResistores arreglo_R;    //antes inicializabamos uno ahora se inicializa un arreglo para tener ahi todosy poder poner un monton en pantalla

//este boton si es estatico y sirve siempre 
static Rectangle resistor_boton = {20, 20, 180, 45};

//====== Para las Fuentes de Tension ======

//falta


//====== Para las Fuentes de Corriente ======

//falta



//----------Seccion de funciones de inicializado y cierre-----------------

//esta funcion genera la ventana de raylib
void InicializarSimulador()
{
    InitWindow(ANCHO, ALTO, "Simulador de Circuitos");
    SetTargetFPS(60);

    //inicializacion de arreglos 
    InicializarArreglo_Res(&arreglo_R, 10); //ojo que se inicializa aca primero pues asi no entra en el while y entra en loop (solo se necesita una vez)
                                        
}

//---------------------------------------UPDATE-------------------------------------

void ActualizarSimulador()
{
    //por ejemplo esto que cambia el estado de la variable bool del resistor creado
    if (ButtonClicked(resistor_boton) == true)
    {
        Anadir_Resistor(&arreglo_R);    //antes se tenia un true, ahora una funcion pues se maneja con arreglos dinamicos(muy parecido al lab 5 solo que con un struct en vez de int)

    }

    //Seccion se seleccion de componentes (proximamente va a estar el movimiento y el snap de cada uno)
    Seleccion_movimiento_resistores(&arreglo_R); //este fue el unico cambio

}

//--------------------------------------DRAWING------------------------------------
void DibujarSimulador(void)
{
    BeginDrawing();

    //--------Zona de trabajo------------
    ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, ANCHO, ALTURA_TOOLBAR, LIGHTGRAY);
    DrawRectangleLines(0, 0, ANCHO, ALTURA_TOOLBAR, BLACK);
    DrawText("Barra de herramientas", (ANCHO / 2) - 100, 25, 20, BLACK);
    Imprimir_Grid();

    //----------Botones para el toolbar(FALTAN MAS)------
    Dibujar_boton(resistor_boton, "Agregar R");

    //dibujado de los componentes, ahora solo se necesita una funcion que en realidad es un loop
    Dibujar_resistor(&arreglo_R);
    

    //----------Respuesta del dibujo al cambio en la actualizacion (FALTAN MAS ACTUALIZACIONES Y MAS COMPONENTES)
    EndDrawing();
}

//funcion de cerrado de la ventana de Raylib
void CerrarSimulador(void)
{
    //ojo que se cierra aca el ciclo y se debe liberar memoria de todos los punteros
    Liberar_Arreglo_Resistores(&arreglo_R);
    CloseWindow();

}

//esta funcion corresponde al grid (la saque del aporte de Aaron)
void Imprimir_Grid(void)
{
    Color gridColor = (Color){200, 200, 200, 255};
    Color majorGridColor = (Color){150, 150, 150, 255};

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