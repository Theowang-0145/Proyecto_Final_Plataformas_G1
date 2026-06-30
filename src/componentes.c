#include "componentes.h"
#include <stdio.h>
#include <stdlib.h>


//====== Para los Resistores (COMPONENTES) ====== (basicamente se cambiaron todas pero se parece al Lab 5)

void InicializarArreglo_Res(ArregloResistores *punt_datos, size_t capacidad_inicial){

    //se inicializa el arreglo segun correposnda (como el lab 5)
    punt_datos->resistores = NULL; 
    punt_datos->tamano=0;
    punt_datos->capacidad=0;

    //NOTA: El puntero dentro del arreglo apunta a varios Resistores que son STRUCTS (Parecido al lab 5)

    //recordar que se le esta guardando memoria a puntero del struct del arreglo del tamano del struct de resistores
    punt_datos->resistores = malloc(capacidad_inicial * sizeof(Resistor)); 


    //manejo de error por punteros 
    if (punt_datos->resistores == NULL){
        printf("\n ERROR NO SE LOGRO GUARDAR MEMORIA PARA EL ARREGLO DINAMICO");
        return;
    }

    punt_datos->capacidad = capacidad_inicial; 
}

void Anadir_Resistor(ArregloResistores *punt_datos){

    //aca se inicializan los resistores cuando hay que anadir uno nuevo, ojo con la posicion que cambia segun el tamano
    //esto para que a la hora de crearlos no se pongan uno sobre otro, sino corridos
    Resistor resistor = {
        .posicion = {(500 + (punt_datos->tamano*40 + 30) ) , (500 + (punt_datos->tamano*40 + 30) )},
        .visible = false,   //se inicializa en false pero al anadirlo hay que ponerlo luego en true
        .seleccionado = false
    };

    //el que se maneje como struct facilita luego cambiarle los valores, seleccionarlo, moverlo y demas

    //manejo de capacidad con realloc
    if (punt_datos->tamano == punt_datos->capacidad){

        size_t nueva_capacidad = punt_datos->capacidad * 2;

        Resistor *nuevo = realloc(punt_datos->resistores, nueva_capacidad * sizeof(Resistor));

        //manejo de error del puntero
        if (nuevo == NULL){
            printf("NO SE PUDO GENERAR NUEVA MEMORIA PARA EL ARREGLO DE RESISTORES");
            return;
        }
        
        //reescripcion del puntero con nueva capacidad
        punt_datos->resistores = nuevo; 
        punt_datos->capacidad = nueva_capacidad;

    }

    //integracion del resistor a la lista del arreglo
    punt_datos->resistores[punt_datos->tamano] = resistor; 
    punt_datos->resistores[punt_datos->tamano].visible = true;
    punt_datos->tamano ++; 

}



void Dibujar_resistor(ArregloResistores *punt_datos)    //esta funcion recibe el struct planteado anteriormente en los 
{   
    //comoo ahora se maneja un arreglo resulta necesario utilizar un ciclo para recorrer todos los resistores y sus variables de posicion
    for (size_t i = 0; i < punt_datos->tamano; i ++ ){

        int x = punt_datos->resistores[i].posicion.x;//aca solo se cambio la notacion y ver que estan dentro de un circlo
        int y = punt_datos->resistores[i].posicion.y;

        DrawLine(x - 60, y, x - 30, y, BLACK);

    //este es el cuadrado de en medio (Recordar que el eje x crece hacia la derecha pero y hacia abajo. Raylib dibuja del punto hacia la derehca y hacia abajo)
        DrawRectangleLines(x - 30, y - 15, 60, 30, BLACK);

    //esta es la linea derecha
        DrawLine(x + 30, y, x + 60, y, BLACK);

    //esto es para el texto dentro del cuadrado
        DrawText("R", x - 12, y - 45, 20, BLACK);
        DrawText("1k", x - 12, y + 25, 18, RED);

        //esta nueva parte es solo un cambio de color si el resistor fue seleccionado
        if (punt_datos->resistores[i].seleccionado == true) {
            DrawLine(x - 60, y, x - 30, y, RED);
            DrawRectangleLines(x - 30, y - 15, 60, 30, RED);
            DrawLine(x + 30, y, x + 60, y, RED);

            DrawText("R", x - 12, y - 45, 20, BLUE);
            DrawText("1k", x - 12, y + 25, 18, BLUE);
        }

    }
}

void Liberar_Arreglo_Resistores(ArregloResistores *punt_datos){
    //este algoritmo ya es base del lab 5 para liberar memoria de los punteros
        if (punt_datos->resistores != NULL)
    {
        free(punt_datos->resistores);

        punt_datos->resistores = NULL;
        punt_datos->tamano = 0;
        punt_datos->capacidad = 0;
    }

    punt_datos->resistores = NULL; 
    punt_datos->capacidad = 0; 
    punt_datos->tamano = 0; 
}

void Seleccion_movimiento_resistores(ArregloResistores *punt_datos){ //basicamente funciona como pulsos generados por el cursor

    bool click;
    bool encima;

    //cada pulso que se genera , primero deselecciona todas las resistencias y luego va egenerando un boton por resistencia, preguntando si esa fue la que toco
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

        Vector2 mouse = GetMousePosition(); //se solicita el estado del mouse y su posicion

        for (size_t i = 0; i < punt_datos->tamano; i++){    //como paso preliminar se deseleccionan todos los elementos

            punt_datos->resistores[i].seleccionado = false; 
        }

        for (size_t i = 0; i < punt_datos->tamano; i++){    //por cada elemento genera su boton y pregunta si fue ese el que se toco

            Rectangle caja_seleccion = Caja_de_seleccion_resistor(punt_datos->resistores[i]); 

            encima = CheckCollisionPointRec(mouse,caja_seleccion);
            click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if ((encima == true) && (click == true)){   //por ultimo, si lo es, simplemente cambia su estado en el strcut para poder ser movido con las teclas proximamente
                punt_datos->resistores[i].seleccionado = true; 
                break;
            }
        }
    }
}

Rectangle Caja_de_seleccion_resistor(Resistor resistor){

    Rectangle caja = {resistor.posicion.x - 70, resistor.posicion.y -50, 130, 70}; 
    return caja; 
} 

void Mover_Resistor(ArregloResistores *punt_datos)
{
    for (size_t i = 0; i < punt_datos->tamano; i++)
    {
        if (punt_datos->resistores[i].seleccionado)
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                punt_datos->resistores[i].posicion.x += 20;
            }

            if (IsKeyPressed(KEY_LEFT))
            {
                punt_datos->resistores[i].posicion.x -= 20;
            }

            if (IsKeyPressed(KEY_UP))
            {
                punt_datos->resistores[i].posicion.y -= 20;
            }

            if (IsKeyPressed(KEY_DOWN))
            {
            punt_datos->resistores[i].posicion.y += 20;
            }

            break;
        }
    }
}


//====== Para las Fuentes de Tension (COMPONENTES) ======

//====== Para las Fuentes de Corriente (COMPONENTES) ======