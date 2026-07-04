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

bool Eliminar_Resistor_Seleccionado(ArregloResistores *punt_datos){
    for (size_t i = 0; i < punt_datos->tamano; i++){
        if (punt_datos->resistores[i].seleccionado){
            for (size_t j = i; j + 1 < punt_datos->tamano; j++){
                punt_datos->resistores[j] = punt_datos->resistores[j + 1];
            }

            punt_datos->tamano--;
            return true;
        }
    }

    return false;
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
/*




//====== Para las Fuentes de Tension (COMPONENTES) ======





*/
void InicializarArreglo_F_T(ArregloFuentes_T *punt_datos, size_t capacidad_inicial){

    //se inicializa el arreglo segun correposnda (como el lab 5)
    punt_datos->fuentes_T = NULL; 
    punt_datos->tamano=0;
    punt_datos->capacidad=0;


    //generando memoria dinamica
    punt_datos->fuentes_T = malloc(capacidad_inicial * sizeof(Fuentes_T)); 


    //manejo de error por punteros 
    if (punt_datos->fuentes_T == NULL){
        printf("\n ERROR NO SE LOGRO GUARDAR MEMORIA PARA EL ARREGLO DINAMICO");
        return;
    }

    punt_datos->capacidad = capacidad_inicial; 
}

void Anadir_Fuente_T(ArregloFuentes_T *punt_datos){

    //inicializacion de una fuente de tension
    Fuentes_T fuentes_T = {
        .posicion = {(600 + (punt_datos->tamano*40 + 30) ) , (500 + (punt_datos->tamano*40 + 30) )},
        .visible = false,   //se inicializa en false pero al anadirlo hay que ponerlo luego en true
        .seleccionado = false
    };


    //manejo de capacidad con realloc
    if (punt_datos->tamano == punt_datos->capacidad){

        size_t nueva_capacidad = punt_datos->capacidad * 2;

        Fuentes_T *nuevo = realloc(punt_datos->fuentes_T, nueva_capacidad * sizeof(Fuentes_T));

        //manejo de error del puntero
        if (nuevo == NULL){
            printf("NO SE PUDO GENERAR NUEVA MEMORIA PARA EL ARREGLO DE RESISTORES");
            return;
        }
        
        //reescripcion del puntero con nueva capacidad
        punt_datos->fuentes_T = nuevo; 
        punt_datos->capacidad = nueva_capacidad;

    }

    //integracion del resistor a la lista del arreglo
    punt_datos->fuentes_T[punt_datos->tamano] = fuentes_T; 
    punt_datos->fuentes_T[punt_datos->tamano].visible = true;
    punt_datos->tamano ++; 

}



void Dibujar_Fuente_T(ArregloFuentes_T *punt_datos) //tal vez el cambio mas importante es este el cambio de dibujo 
{   

    for (size_t i = 0; i < punt_datos->tamano; i ++ ){

        int x = punt_datos->fuentes_T[i].posicion.x;
        int y = punt_datos->fuentes_T[i].posicion.y;

        DrawLine(x - 60, y, x - 25, y, BLACK);//terminal izquierda

        
        DrawCircleLines(x, y, 25, BLACK);//circulo principal
        DrawLine(x + 15, y, x + 5, y, BLUE);//linea horizontal derecha
        DrawLine(x + 10, y-7, x + 10, y+7, BLUE);//linea vertical derecha
        DrawLine(x - 10, y-7, x - 10, y+7, BLUE);//linea vertical izquierda



        DrawLine(x + 25, y, x + 60, y, BLACK);//terminal derecha

        DrawText("V 1", x - 12, y - 45, 20, BLACK);//texto para la fuente
        DrawText("1 mV", x - 12, y + 25, 18, RED);

  
        if (punt_datos->fuentes_T[i].seleccionado == true) {//cambio si es seleccionado
            DrawLine(x - 60, y, x - 25, y, RED);
            DrawCircleLines(x, y, 25, RED);
            DrawLine(x + 15, y, x + 5, y, RED);
            DrawLine(x + 10, y-7, x + 10, y+7, RED);
            DrawLine(x - 10, y-7, x - 10, y+7, RED);
            DrawLine(x + 25, y, x + 60, y, RED);

            DrawText("V 1", x - 12, y - 45, 20, BLUE);
            DrawText("1 mV", x - 12, y + 25, 18, BLUE);
        }

    }
}

void Liberar_Arreglo_Fuente_T(ArregloFuentes_T *punt_datos){

    if (punt_datos->fuentes_T != NULL)
    {
        free(punt_datos->fuentes_T);

        punt_datos->fuentes_T = NULL;
        punt_datos->tamano = 0;
        punt_datos->capacidad = 0;
    }

    punt_datos->fuentes_T = NULL; 
    punt_datos->capacidad = 0; 
    punt_datos->tamano = 0; 
}

bool Eliminar_Fuente_T_Seleccionada(ArregloFuentes_T *punt_datos){
    for (size_t i = 0; i < punt_datos->tamano; i++){
        if (punt_datos->fuentes_T[i].seleccionado){
            for (size_t j = i; j + 1 < punt_datos->tamano; j++){
                punt_datos->fuentes_T[j] = punt_datos->fuentes_T[j + 1];
            }

            punt_datos->tamano--;
            return true;
        }
    }

    return false;
}

void Seleccion_movimiento_Fuente_T(ArregloFuentes_T *punt_datos){ 

    bool click;
    bool encima;

    //cada pulso que se genera , primero deselecciona todas las resistencias y luego va egenerando un boton por resistencia, preguntando si esa fue la que toco
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

        Vector2 mouse = GetMousePosition(); //se solicita el estado del mouse y su posicion

        for (size_t i = 0; i < punt_datos->tamano; i++){    //como paso preliminar se deseleccionan todos los elementos

            punt_datos->fuentes_T[i].seleccionado = false; 
        }

        for (size_t i = 0; i < punt_datos->tamano; i++){    //por cada elemento genera su boton y pregunta si fue ese el que se toco

            Rectangle caja_seleccion = Caja_de_seleccion_Fuente_T(punt_datos->fuentes_T[i]); 

            encima = CheckCollisionPointRec(mouse,caja_seleccion);
            click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if ((encima == true) && (click == true)){   //por ultimo, si lo es, simplemente cambia su estado en el strcut para poder ser movido con las teclas proximamente
                punt_datos->fuentes_T[i].seleccionado = true; 
                break;
            }
        }
    }
}

Rectangle Caja_de_seleccion_Fuente_T(Fuentes_T fuentes_T){  //y este es el segundo cambio mas importante que es cambiarle la zona de seleccion

    Rectangle caja = {fuentes_T.posicion.x - 70, fuentes_T.posicion.y -50, 150, 90}; 
    return caja; 
} 

void Mover_Fuente_T(ArregloFuentes_T *punt_datos)
{
    for (size_t i = 0; i < punt_datos->tamano; i++)
    {
        if (punt_datos->fuentes_T[i].seleccionado)
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                punt_datos->fuentes_T[i].posicion.x += 20;
            }

            if (IsKeyPressed(KEY_LEFT))
            {
                punt_datos->fuentes_T[i].posicion.x -= 20;
            }

            if (IsKeyPressed(KEY_UP))
            {
                punt_datos->fuentes_T[i].posicion.y -= 20;
            }

            if (IsKeyPressed(KEY_DOWN))
            {
            punt_datos->fuentes_T[i].posicion.y += 20;
            }

            break;
        }
    }
}
/*




//====== Para las Fuentes de Corriente (COMPONENTES) ======





*/
void InicializarArreglo_F_C(ArregloFuentes_C *punt_datos, size_t capacidad_inicial){

    
    punt_datos->fuentes_C = NULL; 
    punt_datos->tamano=0;
    punt_datos->capacidad=0;



    //recordar que se le esta guardando memoria a puntero del struct del arreglo del tamano del struct de resistores
    punt_datos->fuentes_C = malloc(capacidad_inicial * sizeof(Fuentes_T)); 


    //manejo de error por punteros 
    if (punt_datos->fuentes_C == NULL){
        printf("\n ERROR NO SE LOGRO GUARDAR MEMORIA PARA EL ARREGLO DINAMICO");
        return;
    }

    punt_datos->capacidad = capacidad_inicial; 
}

void Anadir_Fuente_C(ArregloFuentes_C *punt_datos){

    //se inicializa una nueva fuente de corriente 
    Fuentes_C fuentes_C = {
        .posicion = {(700 + (punt_datos->tamano*40 + 30) ) , (500 + (punt_datos->tamano*40 + 30) )},
        .visible = false,   //se inicializa en false pero al anadirlo hay que ponerlo luego en true
        .seleccionado = false
    };



    //manejo de capacidad con realloc
    if (punt_datos->tamano == punt_datos->capacidad){

        size_t nueva_capacidad = punt_datos->capacidad * 2;

        Fuentes_C *nuevo = realloc(punt_datos->fuentes_C, nueva_capacidad * sizeof(Fuentes_C));

        //manejo de error del puntero
        if (nuevo == NULL){
            printf("NO SE PUDO GENERAR NUEVA MEMORIA PARA EL ARREGLO DE RESISTORES");
            return;
        }
        
        //reescripcion del puntero con nueva capacidad
        punt_datos->fuentes_C = nuevo; 
        punt_datos->capacidad = nueva_capacidad;

    }

    //integracion del resistor a la lista del arreglo
    punt_datos->fuentes_C[punt_datos->tamano] = fuentes_C; 
    punt_datos->fuentes_C[punt_datos->tamano].visible = true;
    punt_datos->tamano ++; 

}



void Dibujar_Fuente_C(ArregloFuentes_C *punt_datos)
{   
   //ciclo para impresion constante de todas las fuentes
    for (size_t i = 0; i < punt_datos->tamano; i ++ ){

        int x = punt_datos->fuentes_C[i].posicion.x;
        int y = punt_datos->fuentes_C[i].posicion.y;

        DrawLine(x - 60, y, x - 25, y, BLACK);

        //este es el dibujo del circulo 
        DrawCircleLines(x, y, 25, BLACK);
        DrawLine(x - 10, y, x+10, y , BLUE); //linea horizontal
        DrawLine(x + 10, y, x , y - 10 , BLUE);//linea inclinada superior
        DrawLine(x + 10, y, x , y + 10 , BLUE);//linea inclinada inferior

    //esta es la linea derecha
        DrawLine(x + 25, y, x + 60, y, BLACK);

    //esto es para el texto de la fuente
        DrawText("I 1", x - 12, y - 45, 20, BLACK);
        DrawText("1 mA", x - 12, y + 25, 18, RED);

        //cambio de color si es seleccionado
        if (punt_datos->fuentes_C[i].seleccionado == true) {

            DrawLine(x - 60, y, x - 25, y, RED);
            DrawCircleLines(x, y, 25, RED);
            DrawLine(x - 10, y, x+10, y , RED);
            DrawLine(x + 10, y, x , y - 10 , RED);
            DrawLine(x + 10, y, x , y + 10 , RED);
            DrawLine(x + 25, y, x + 60, y, RED);

            DrawText("I 1", x - 12, y - 45, 20, BLUE);
            DrawText("1 mA", x - 12, y + 25, 18, BLUE);
        }

    }
}

void Liberar_Arreglo_Fuente_C(ArregloFuentes_C *punt_datos){
        //liberacion de memoria para los punteros
        if (punt_datos->fuentes_C != NULL)
    {
        free(punt_datos->fuentes_C);

        punt_datos->fuentes_C = NULL;
        punt_datos->tamano = 0;
        punt_datos->capacidad = 0;
    }

    punt_datos->fuentes_C = NULL; 
    punt_datos->capacidad = 0; 
    punt_datos->tamano = 0; 
}

bool Eliminar_Fuente_C_Seleccionada(ArregloFuentes_C *punt_datos){
    for (size_t i = 0; i < punt_datos->tamano; i++){
        if (punt_datos->fuentes_C[i].seleccionado){
            for (size_t j = i; j + 1 < punt_datos->tamano; j++){
                punt_datos->fuentes_C[j] = punt_datos->fuentes_C[j + 1];
            }

            punt_datos->tamano--;
            return true;
        }
    }

    return false;
}

void Seleccion_movimiento_Fuente_C(ArregloFuentes_C *punt_datos){ //basicamente funciona como pulsos generados por el cursor

    bool click;
    bool encima;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

        Vector2 mouse = GetMousePosition(); //se solicita el estado del mouse y su posicion

        for (size_t i = 0; i < punt_datos->tamano; i++){    //como paso preliminar se deseleccionan todos los elementos

            punt_datos->fuentes_C[i].seleccionado = false; 
        }

        for (size_t i = 0; i < punt_datos->tamano; i++){    //por cada elemento genera su boton y pregunta si fue ese el que se toco

            Rectangle caja_seleccion = Caja_de_seleccion_Fuente_C(punt_datos->fuentes_C[i]); 

            encima = CheckCollisionPointRec(mouse,caja_seleccion);
            click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if ((encima == true) && (click == true)){   //por ultimo, si lo es, simplemente cambia su estado en el strcut para poder ser movido con las teclas proximamente
                punt_datos->fuentes_C[i].seleccionado = true; 
                break;
            }
        }
    }
}

Rectangle Caja_de_seleccion_Fuente_C(Fuentes_C fuentes_C){  //cajita de la fuente de corriente por si es seleccionado

    Rectangle caja = {fuentes_C.posicion.x - 70, fuentes_C.posicion.y -50, 150, 90}; 
    return caja; 
} 

void Mover_Fuente_C(ArregloFuentes_C *punt_datos)
{
    for (size_t i = 0; i < punt_datos->tamano; i++)
    {
        if (punt_datos->fuentes_C[i].seleccionado)
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                punt_datos->fuentes_C[i].posicion.x += 20;
            }

            if (IsKeyPressed(KEY_LEFT))
            {
                punt_datos->fuentes_C[i].posicion.x -= 20;
            }

            if (IsKeyPressed(KEY_UP))
            {
                punt_datos->fuentes_C[i].posicion.y -= 20;
            }

            if (IsKeyPressed(KEY_DOWN))
            {
            punt_datos->fuentes_C[i].posicion.y += 20;
            }

            break;
        }
    }
}

/*

//====== Para los Nodos (COMPONENTES) ======


*/
void InicializarArregloNodo(ArregloNodos *punt_datos, size_t capacidad_inicial){

    
    punt_datos->nodo = NULL; 
    punt_datos->tamano=0;
    punt_datos->capacidad=0;



    //recordar que se le esta guardando memoria a puntero del struct del arreglo del tamano del struct de resistores
    punt_datos->nodo = malloc(capacidad_inicial * sizeof(Fuentes_T)); 


    //manejo de error por punteros 
    if (punt_datos->nodo == NULL){
        printf("\n ERROR NO SE LOGRO GUARDAR MEMORIA PARA EL ARREGLO DINAMICO");
        return;
    }

    punt_datos->capacidad = capacidad_inicial; 
}

void Anadir_Nodo(ArregloNodos *punt_datos){

    //se inicializa una nueva fuente de corriente 
    Nodo nodo = {
        .posicion = {(800 + (punt_datos->tamano*40 + 30) ) , (500 + (punt_datos->tamano*40 + 30) )},
        .visible = false,   //se inicializa en false pero al anadirlo hay que ponerlo luego en true
        .seleccionado = false
    };



    //manejo de capacidad con realloc
    if (punt_datos->tamano == punt_datos->capacidad){

        size_t nueva_capacidad = punt_datos->capacidad * 2;

        Nodo *nuevo = realloc(punt_datos->nodo, nueva_capacidad * sizeof(Nodo));

        //manejo de error del puntero
        if (nuevo == NULL){
            printf("NO SE PUDO GENERAR NUEVA MEMORIA PARA EL ARREGLO DE RESISTORES");
            return;
        }
        
        //reescripcion del puntero con nueva capacidad
        punt_datos->nodo = nuevo; 
        punt_datos->capacidad = nueva_capacidad;

    }

    //integracion del resistor a la lista del arreglo
    punt_datos->nodo[punt_datos->tamano] = nodo; 
    punt_datos->nodo[punt_datos->tamano].visible = true;
    punt_datos->tamano ++; 

}



void Dibujar_Nodo(ArregloNodos *punt_datos)
{   
   //ciclo para impresion constante de todas las fuentes
    for (size_t i = 0; i < punt_datos->tamano; i ++ ){

        int x = punt_datos->nodo[i].posicion.x;
        int y = punt_datos->nodo[i].posicion.y;

            DrawCircle(x, y, 10, BLUE);
            DrawText("Nodo", x-20, y-30, 20, BLACK);
            DrawText("1", x-1, y+13, 18, BLACK);

        //cambio de color si es seleccionado
        if (punt_datos->nodo[i].seleccionado == true) {

            DrawCircle(x, y, 10, RED);
            DrawText("Nodo", x-20, y-30, 20, BLUE);
            DrawText("1", x-1, y+13, 18, BLUE);
        }

    }
}

void Liberar_Arreglo_Nodo(ArregloNodos *punt_datos){
        //liberacion de memoria para los punteros
        if (punt_datos->nodo != NULL)
    {
        free(punt_datos->nodo);

        punt_datos->nodo = NULL;
        punt_datos->tamano = 0;
        punt_datos->capacidad = 0;
    }

    punt_datos->nodo = NULL; 
    punt_datos->capacidad = 0; 
    punt_datos->tamano = 0; 
}

bool Eliminar_Nodo_Seleccionado(ArregloNodos *punt_datos){
    for (size_t i = 0; i < punt_datos->tamano; i++){
        if (punt_datos->nodo[i].seleccionado){
            for (size_t j = i; j + 1 < punt_datos->tamano; j++){
                punt_datos->nodo[j] = punt_datos->nodo[j + 1];
            }

            punt_datos->tamano--;
            return true;
        }
    }

    return false;
}

void Seleccion_movimiento_Nodo(ArregloNodos *punt_datos){ //basicamente funciona como pulsos generados por el cursor

    bool click;
    bool encima;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

        Vector2 mouse = GetMousePosition(); //se solicita el estado del mouse y su posicion

        for (size_t i = 0; i < punt_datos->tamano; i++){    //como paso preliminar se deseleccionan todos los elementos

            punt_datos->nodo[i].seleccionado = false; 
        }

        for (size_t i = 0; i < punt_datos->tamano; i++){    //por cada elemento genera su boton y pregunta si fue ese el que se toco

            Rectangle caja_seleccion = Caja_de_seleccion_Nodo(punt_datos->nodo[i]); 

            encima = CheckCollisionPointRec(mouse,caja_seleccion);
            click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if ((encima == true) && (click == true)){   //por ultimo, si lo es, simplemente cambia su estado en el strcut para poder ser movido con las teclas proximamente
                punt_datos->nodo[i].seleccionado = true; 
                break;
            }
        }
    }
}

Rectangle Caja_de_seleccion_Nodo(Nodo Nodo){  //cajita de la fuente de corriente por si es seleccionado

    Rectangle caja = {Nodo.posicion.x - 20, Nodo.posicion.y -20, 30, 30}; 
    return caja; 
} 

void Mover_Nodo(ArregloNodos *punt_datos)
{
    for (size_t i = 0; i < punt_datos->tamano; i++)
    {
        if (punt_datos->nodo[i].seleccionado)
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                punt_datos->nodo[i].posicion.x += 20;
            }

            if (IsKeyPressed(KEY_LEFT))
            {
                punt_datos->nodo[i].posicion.x -= 20;
            }

            if (IsKeyPressed(KEY_UP))
            {
                punt_datos->nodo[i].posicion.y -= 20;
            }

            if (IsKeyPressed(KEY_DOWN))
            {
            punt_datos->nodo[i].posicion.y += 20;
            }

            break;
        }
    }
}
