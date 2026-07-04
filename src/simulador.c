#include "botones.h"
#include "componentes.h"
#include "simulador.h"

#include <raylib.h>
#include <stdio.h>

//----------Seccion de posicones y dimensiones de componentes(dibujo del componente y su boton asociado)-----------------

//====== Para los Componentes ======

ArregloResistores arreglo_R; 
ArregloFuentes_T arreglo_F_T;
ArregloFuentes_C arreglo_F_C;
ArregloNodos arreglo_nodo;

//este boton si es estatico y sirve siempre 
static Rectangle resistor_boton = {20, 20, 180, 45};
static Rectangle fuente_T_boton = {20, 80, 180, 45};
static Rectangle fuente_C_boton = {220, 20, 180, 45};
static Rectangle nodo_boton = {220, 80, 180, 45};
static Rectangle rotar_boton = {420, 20, 150, 45};
static Rectangle eliminar_boton = {420, 80, 150, 45};



//----------Seccion de funciones de inicializado y cierre-----------------

//esta funcion genera la ventana de raylib
void InicializarSimulador()
{
    InitWindow(ANCHO, ALTO, "Simulador de Circuitos");
    SetTargetFPS(60);

    //inicializacion de arreglos 
    InicializarArreglo_Res(&arreglo_R, 10); //ojo que se inicializa aca primero pues asi no entra en el while y entra en loop (solo se necesita una vez)              
    InicializarArreglo_F_T(&arreglo_F_T, 10);
    InicializarArreglo_F_C(&arreglo_F_C, 10);
    InicializarArregloNodo(&arreglo_nodo, 10);
}

//---------------------------------------UPDATE-------------------------------------

void ActualizarSimulador()
{
    //por ejemplo esto que cambia el estado de la variable bool del resistor creado
    if (ButtonClicked(resistor_boton) == true)
    {
        Anadir_Resistor(&arreglo_R);    //antes se tenia un true, ahora una funcion pues se maneja con arreglos dinamicos(muy parecido al lab 5 solo que con un struct en vez de int)

    }

    if(ButtonClicked(fuente_T_boton) == true){

        Anadir_Fuente_T(&arreglo_F_T);
    }

    if(ButtonClicked(fuente_C_boton) == true){

        Anadir_Fuente_C(&arreglo_F_C);
    }

    if(ButtonClicked(nodo_boton) == true){

        Anadir_Nodo(&arreglo_nodo);
    }


    if(ButtonClicked(rotar_boton) == true){

        printf("Rotar componente"); 
    }

    if(ButtonClicked(eliminar_boton) == true){

        bool eliminado = false;

        eliminado = Eliminar_Resistor_Seleccionado(&arreglo_R) || eliminado;
        eliminado = Eliminar_Fuente_T_Seleccionada(&arreglo_F_T) || eliminado;
        eliminado = Eliminar_Fuente_C_Seleccionada(&arreglo_F_C) || eliminado;
        eliminado = Eliminar_Nodo_Seleccionado(&arreglo_nodo) || eliminado;

        if (eliminado){
        printf("Componente Eliminado");
        }
        else {
        printf("Seleccione un componente antes de eliminar");
        }
    }

    //Seccion se seleccion de componentes (proximamente va a estar el movimiento y el snap de cada uno)
    Seleccion_movimiento_resistores(&arreglo_R); //este fue el unico cambio
    Mover_Resistor(&arreglo_R); //para mover el resistor basta con hacer una funcion nueva que recorra el arreglo, busque el seleccionado y cambie su vector con punteros

    Seleccion_movimiento_Fuente_T(&arreglo_F_T);
    Mover_Fuente_T(&arreglo_F_T);

    Seleccion_movimiento_Fuente_C(&arreglo_F_C);
    Mover_Fuente_C(&arreglo_F_C);

    Seleccion_movimiento_Nodo(&arreglo_nodo);
    Mover_Nodo(&arreglo_nodo);
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
    DrawText("[ DC SIMULATOR ]", (ANCHO / 2) - 105, 80, 29, BLACK);

    DrawRectangle(890, 10, 475, 130, WHITE);
    DrawRectangleLines(890, 10, 475, 130, BLACK);
    DrawText("Mensajes",1080, 25, 20, BLACK);

    Imprimir_Grid();

    //----------Botones para el toolbar(FALTAN MAS)------
    Dibujar_boton(resistor_boton, "Agregar R");
    Dibujar_boton(fuente_T_boton, "Agregar F-T");
    Dibujar_boton(fuente_C_boton, "Agregar F-C");
    Dibujar_boton(nodo_boton, "Agregar N");
    Dibujar_boton(rotar_boton, "Rotar Comp");
    Dibujar_boton(eliminar_boton, "Eliminar");

    //dibujado de los componentes, ahora solo se necesita una funcion que en realidad es un loop
    Dibujar_resistor(&arreglo_R);
    Dibujar_Fuente_T(&arreglo_F_T);
    Dibujar_Fuente_C(&arreglo_F_C);
    Dibujar_Nodo(&arreglo_nodo);
    

    //----------Respuesta del dibujo al cambio en la actualizacion (FALTAN MAS ACTUALIZACIONES Y MAS COMPONENTES)
    EndDrawing();
}

//funcion de cerrado de la ventana de Raylib
void CerrarSimulador(void)
{
    //ojo que se cierra aca el ciclo y se debe liberar memoria de todos los punteros
    Liberar_Arreglo_Resistores(&arreglo_R);
    Liberar_Arreglo_Fuente_T(&arreglo_F_T);
    Liberar_Arreglo_Fuente_C(&arreglo_F_C);
    Liberar_Arreglo_Nodo(&arreglo_nodo);
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
