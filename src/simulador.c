#include "botones.h"
#include "componentes.h"
#include "simulador.h"

#include <raylib.h>
#include <stdio.h>

//----------Seccion de posicones y dimensiones de componentes(dibujo del componente y su boton asociado)-----------------

//====== Para los Resistores ======

//este struct guarda UN SOLO RESISTOR POR AHORA, pues se quiere tener la base. 
//cambiarlo luego para que puedan haber mas resistores, con una lsta o con un arreglo dinamico

static Resistor resistor = {

    .posicion = {500, 500},
    .visible = false    //inicializado en false pues no se ve en pantalla desde el inicio, sino mediante un cambio con bool
};

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
}

//esta funcion actualiza constantemente lo que ocurre en el programa, es decir, realiza todos los cambios que luego 
//en la creacion del dibujo se ven reflejados

void ActualizarSimulador()
{
    //por ejemplo esto que cambia el estado de la variable bool del resistor creado
    if (ButtonClicked(resistor_boton) == true)
    {
        resistor.visible = true;
    }


    //aca van a hacer falta muchas mas funciones para las demas innteracciones

}


//esta es la funcion de dibujado de zona de trabajo, de componentes y de cambios en el programa
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


    //----------Respuesta del dibujo al cambio en la actualizacion (FALTAN MAS ACTUALIZACIONES Y MAS COMPONENTES)
    if (resistor.visible == true)
    {
        Dibujar_resistor(resistor);
    }
    EndDrawing();
}

//funcion de cerrado de la ventana de Raylib
void CerrarSimulador(void)
{
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