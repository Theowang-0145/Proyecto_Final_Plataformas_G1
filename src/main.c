/*
*Esta es la seccion de main donde solamente se encuentran las funciones de inicializacion, dibujado, actualizado, y cierre.
*esto para no contaminar mucho el archivo.Note que se include un header file, ese header file contiene absolutamente todo
*/

#include "simulador.h"

int main(void)
{
    InicializarSimulador();

    while (!WindowShouldClose())
    {
        ActualizarSimulador();
        DibujarSimulador();
    }

    CerrarSimulador();

    return 0;
}