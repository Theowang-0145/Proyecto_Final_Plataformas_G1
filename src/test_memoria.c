/*

Compruebe que no hay memory leaks con el comando make memcheck-test el cual compila solo este .c y el de componentes .c

Esto mismo se puede usar para los demas

*/



#include "componentes.h"
#include <stdio.h>
#include <raylib.h>

//basicamente se va a hacer un memory test con este archivo pues se utilizan punteros para varias cosas
//entonces es como jugar con las funciones ya hechas, las cuales no tienen practicamente nada de raylib, simplemente es la logica detras del funcionamiento de todo esto
//aun asi se pone por si se llegase a utilizar algo, por ejemplo como lo de los vectores
int main(void)
{
    //entonces como esta es la parte logica de manero de componentes como variable se puede hacer un .c aparte para verificar los memory leaks

    //aca se inicializa
    ArregloResistores arreglo;

    InicializarArreglo_Res(&arreglo, 10);

    //aca se van a;adiendo resistores cada uno variando sus posiciones pero
    for (int i = 0; i < 20; i++)
    {
        Anadir_Resistor(&arreglo);
    }

    Liberar_Arreglo_Resistores(&arreglo);

    return 0;
}