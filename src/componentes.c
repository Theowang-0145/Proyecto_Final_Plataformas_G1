#include "componentes.h"
#include <stdio.h>
#include <stdlib.h>


/*

NOTA: Toda esta seccion de codigo pertenece al las propiedades de cada componente. En resumen cada componente es un struct que posee 
dibujo, vectores, visibilidad, seleccion y valores de nombre y de numero. Si se observa bien, cada componente es una copia del otro 
pero con otros nombres y dibujos para poder diferenciarlos, pero poseen las mismas caracteristicas de movimiento, seleccion y eliminado.
Cabe resaltar que al ser objetos de diseno, se deben de seleccionar de alguna forma, por ello se implementan Rectangles para poder tratarlos
como objetos moviles si son clickeados por el cursor (como si fueran un boton). 

*/


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
	//se debe agregar la conticion inicial de rotacion, en este caso horizontal
	.rotacion = 0,
	//ademas de añadir la condicion inicial de coneccion de los componentes, -1 significa no conectado
	//.nodo_inicio = -1,
	//.nodo_fin = -1
    };

    snprintf(resistor.nombre, MAX_TEXTO_COMPONENTE, "R%zu", punt_datos->tamano + 1);
    snprintf(resistor.valor, MAX_TEXTO_COMPONENTE, "1k");

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

//el siguiente void permite conectar el componente con el nodo
//void Conectar_Resistor(ArregloResistores *punt_datos, int indice_resistor, int nodo_inicio, int nodo_fin) {
    //if(indice_resistor < 0 || indice_resistor >= punt_datos->tamano) {
	//se comprueban dos cosas, primero, que el indice sea negativo para que este desconectado
	//y que luego, que el indice sea disdinto de los otros componentes
	//return;
    //}
    //punt_datos->resistores[indice_resistor].nodo_inicio = nodo_inicio;//aca se otorga el valor del primer nodo
    //punt_datos->resistores[indice_resistor].nodo_fin = nodo_fin;//y aca el segundo nodo
//}

//el siguiente dibuja la coneccion entre el componente y el nodo, el resistor es de coneccion roja
//void Dibujar_Conexiones_Resistores(ArregloResistores *resistores, ArregloNodos *nodos) {
    //for(size_t i = 0; i < resistores->tamano; i++) { //este es un cliclo de definicion nada mas
        //int inicio = resistores->resistores[i].nodo_inicio;//sse establece el valor de los nodos
        //int fin = resistores->resistores[i].nodo_fin;
        //if(inicio < 0 || fin < 0) {
            //continue;
        //}
        //Vector2 p1 = nodos->nodo[inicio].posicion;
        //Vector2 p2 = nodos->nodo[fin].posicion;
        //DrawLineEx(p1, p2, 3, RED);//cable rojo para distinguir
    //}
//}



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
        DrawText(punt_datos->resistores[i].nombre, x - 12, y - 45, 20, BLACK);
        DrawText(punt_datos->resistores[i].valor, x - 12, y + 25, 18, RED);

        //esta nueva parte es solo un cambio de color si el resistor fue seleccionado
	//ademas, se agrega la condicion que permite la rotacion al seleccionar usando boton R sobre el componente
        if (punt_datos->resistores[i].seleccionado == true) {
		if(punt_datos->resistores[i].rotacion == 0) {
        		DrawLine(x - 60, y, x - 30, y, RED);
       	 		DrawRectangleLines(x - 30, y - 15, 60, 30, RED);
        		DrawLine(x + 30, y, x + 60, y, RED);
    		}
    		else {
        		DrawLine(x, y - 60, x, y - 30, RED);
        		DrawRectangleLines(x - 15, y - 30, 30, 60, RED);
        		DrawLine(x, y + 30, x, y + 60, RED);
		}
            	DrawText(punt_datos->resistores[i].nombre, x - 12, y - 45, 20, BLUE);
            	DrawText(punt_datos->resistores[i].valor, x - 12, y + 25, 18, BLUE);
	}
	//esto agrega las condiciones para la rotacion del componente
	//esta primera condicion determina si esta en horizontal
	if (punt_datos->resistores[i].rotacion == 0) {
		Drawline(x - 60, y, x - 30,y, BLACK);
		DrawRectangleLines(x - 30, y - 15, 60, 30, BLACK);
	}
	else { //mientras que esta cambia la forma en vertical 
		DrawLine(x, y - 60, x, y - 30, BLACK);
		DrawRectangleLines(x - 15, y - 30, 30, 60, BLACK);
		DrawLine(x, y + 30, x, y + 60, BLACK);
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

//aca se agrega el codigo que permite la rotacion
void Rotar_Resistor(ArregloResistores *punt_datos) {
	for(size_t i = 0; i < punt_datos->tamano; i++) {
		if(punt_datos->resistores[i].seleccionado) {
			if(punt_datos->resistores[i].rotacion == 0) {
				punt_datos->resistores[i].rotacion = 1; //mientras que aca se evalua si es vertical
			}
			else {
				punt_datos->resistores[i].rotacion = 0; //esto permite que siempre este en horrizantal 
			}
			break;
		}
	}
}
//fin de agregado para rotar

void Mover_Resistor(ArregloResistores *punt_datos)
{
    for (size_t i = 0; i < punt_datos->tamano; i++)//esto aplica para todos los resitorores, por eso el ciclo for
    {
        if (punt_datos->resistores[i].seleccionado)
        {
            if (IsKeyDown(KEY_RIGHT))
            {
                punt_datos->resistores[i].posicion.x += 5;
            }

            if (IsKeyDown(KEY_LEFT))
            {
                punt_datos->resistores[i].posicion.x -= 5;
            }

            if (IsKeyDown(KEY_UP))
            {
                punt_datos->resistores[i].posicion.y -= 5;
            }

            if (IsKeyDown(KEY_DOWN))
            {
            punt_datos->resistores[i].posicion.y += 5;
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

//el siguiente void permite conectar el componente con el nodo

//void Conectar_Fuente_T(ArregloFuentes_T *punt_datos, int indice_fuente_T, int nodo_inicio, int nodo_fin) {
    //if(indice_fuente_T < 0 || indice_fuente_T >= punt_datos->tamano) {
        //return;
    //}
    //punt_datos->fuentes_T[indice_fuente_T].nodo_inicio = nodo_inicio;
    //punt_datos->fuentes_T[indice_fuente_T].nodo_fin = nodo_fin;
//}

//el siguiente vaoid establece la coneccion de fuente de tencion en color azul para visualizarlo
//void Dibujar_Conexiones_Fuentes_T(ArregloFuentes_T *fuentes_T, ArregloNodos *nodos) {
    //for(size_t i = 0; i < fuentes_T->tamano; i++) {
        //int inicio = fuentes_T->fuentes_T[i].nodo_inicio;
        //int fin = fuentes_T->fuentes_T[i].nodo_fin;
        //if(inicio < 0 || fin < 0) {
            //continue;
        //}
        //Vector2 p1 = nodos->nodo[inicio].posicion;
        //Vector2 p2 = nodos->nodo[fin].posicion;
        //DrawLineEx(p1, p2, 3, BLUE);//COLOR AZUL PARA DETERMINAR CONEXION
    //}
//}


void Anadir_Fuente_T(ArregloFuentes_T *punt_datos){

    //inicializacion de una fuente de tension
    Fuentes_T fuentes_T = {
        .posicion = {(600 + (punt_datos->tamano*40 + 30) ) , (500 + (punt_datos->tamano*40 + 30) )},
        .visible = false,   //se inicializa en false pero al anadirlo hay que ponerlo luego en true
        .seleccionado = false
        //se debe agregar la conticion inicial de rotacion, en este caso horizontal
        .rotacion = 0
        //ademas de añadir la condicion inicial de coneccion de los componentes, -1 significa no conectado
        //.nodo_inicio = -1,
        //.nodo_fin = -1
    };

    snprintf(fuentes_T.nombre, MAX_TEXTO_COMPONENTE, "V%zu", punt_datos->tamano + 1);
    snprintf(fuentes_T.valor, MAX_TEXTO_COMPONENTE, "1mV");


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

//en esta seccion se debe hacer un cambio en el diseño, antes, solo se dibujaba, pero al agregarse la rotacion, no basta con el diseño basico 
	for (size_t i = 0; i < punt_datos->tamano; i++) {
		//aca se dejo la tipografia del texto
		DrawText(punt_datos->fuentes_T[i].nombre, x -12, y - 45, 20, BLUE);
		DrawText(punt_datos->fuentes_T[i].valor, x - 12, y + 25, 18, BLUE);

		if(punt_datos->fuentes_T[i].rotacion == 0) {
			DrawLine(x - 60, y, x - 25, y, BLACK);//terminal izquierdo
			DrawCircleLines(x, y, 25, BLACK);//el circulo principal
			DrawLine(x + 15, y, x + 5, y, BLUE);//linea horizontal derecha
			DrawLine(x + 10, y-7, x + 10, y+7, BLUE);//linea vertical derecha
    			DrawLine(x - 10, y-7, x - 10, y+7, BLUE);//linea vertical izquierda
    			DrawLine(x + 25, y, x + 60, y, BLACK);//linea horizontal izquierda
		}
		else {
    			DrawLine(x, y - 60, x, y - 25, BLACK);
			DrawCircleLines(x, y, 25, BLACK);
 			//Rotacion para el simbolo interno
    			DrawLine(x, y - 15, x, y - 5, BLUE);
    			DrawLine(x - 7, y - 10, x + 7, y - 10, BLUE);
    			DrawLine(x - 7, y + 10, x + 7, y + 10, BLUE);
   			DrawLine(x, y + 25, x, y + 60, BLACK);
		}
	}
        //al igual que en el dibujado, el seleccionado debe cambiar la estructura para rotar.

		if (punt_datos->fuentes_T[i].seleccionado == true) {
    			if(punt_datos->fuentes_T[i].rotacion == 0) {
        		//aca se respeta el mismo orden de lineas pera cambiando de horizontal a vertital y viceversa
				DrawLine(x - 60, y, x - 25, y, RED);
        			DrawCircleLines(x, y, 25, RED);
        			DrawLine(x + 15, y, x + 5, y, RED);
        			DrawLine(x + 10, y-7, x + 10, y+7, RED);
       				DrawLine(x - 10, y-7, x - 10, y+7, RED);
        			DrawLine(x + 25, y, x + 60, y, RED);
    			}
    			else {
        			DrawLine(x, y - 60, x, y - 25, RED);
        			DrawCircleLines(x, y, 25, RED);
        			DrawLine(x, y - 15, x, y - 5, RED);
        			DrawLine(x - 7, y - 10, x + 7, y - 10, RED);
        			DrawLine(x - 7, y + 10, x + 7, y + 10, RED);
        			DrawLine(x, y + 25, x, y + 60, RED);
   			}
	//se mantine la tipografia del texto
    			DrawText(punt_datos->fuentes_T[i].nombre, x - 12, y - 45, 20, BLUE);
    			DrawText(punt_datos->fuentes_T[i].valor, x - 12, y + 25, 18, BLUE);
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

//aca se agrega el codigo que permite la rotacion 
void Rotar_Fuente_T(ArregloFuentes_T *punt_datos) {
        for(size_t i = 0; i < punt_datos->tamano; i++) {
                if(punt_datos->fuentes_T[i].seleccionado) {
                        if(punt_datos->fuentes_T[i].rotacion == 0) {
                                punt_datos->fuentes_T[i].rotacion = 1; //mientras que aca se evalua si e>
                        }
                        else {
                                punt_datos->fuentes_T[i].rotacion = 0; //esto permite que siempre este e>
                        }
                        break;
                }
        }
}
//fin de agregado para rotar

void Mover_Fuente_T(ArregloFuentes_T *punt_datos)
{
    for (size_t i = 0; i < punt_datos->tamano; i++)
    {
        if (punt_datos->fuentes_T[i].seleccionado)
        {
            if (IsKeyDown(KEY_RIGHT))
            {
                punt_datos->fuentes_T[i].posicion.x += 5;
            }

            if (IsKeyDown(KEY_LEFT))
            {
                punt_datos->fuentes_T[i].posicion.x -= 5;
            }

            if (IsKeyDown(KEY_UP))
            {
                punt_datos->fuentes_T[i].posicion.y -= 5;
            }

            if (IsKeyDown(KEY_DOWN))
            {
            punt_datos->fuentes_T[i].posicion.y += 5;
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
        //se debe agregar la conticion inicial de rotacion, en este caso horizontal
        .rotacion = 0
        //ademas de añadir la condicion inicial de coneccion de los componentes, -1 significa no conectado
        //.nodo_inicio = -1,
        //.nodo_fin = -1
    };

    snprintf(fuentes_C.nombre, MAX_TEXTO_COMPONENTE, "I%zu", punt_datos->tamano + 1);
    snprintf(fuentes_C.valor, MAX_TEXTO_COMPONENTE, "1mA");


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

//funcion de conexion en fuente de corriente

//void Conectar_Fuente_C(ArregloFuentes_C *punt_datos, int indice_fuente_C, int nodo_inicio, int nodo_fin) {
    //if(indice_fuente_C < 0 || indice_fuente_C >= punt_datos->tamano) {
        //return;
    //}
    //punt_datos->fuentes_C[indice_fuente_C].nodo_inicio = nodo_inicio;
    //punt_datos->fuentes_C[indice_fuente_C].nodo_fin = nodo_fin;
//}

//Funcion para dibujar coneccion de fuente de corriente en color verde 

//void Dibujar_Conexiones_Fuentes_C(ArregloFuentes_C *fuentes_C, ArregloNodos *nodos) {
    //for(size_t i = 0; i < fuentes_C->tamano; i++) {
        //int inicio = fuentes_C->fuentes_C[i].nodo_inicio;
        //int fin = fuentes_C->fuentes_C[i].nodo_fin;
        //if(inicio < 0 || fin < 0) {
            //continue;
        //}
        //Vector2 p1 = nodos->nodo[inicio].posicion;
        //Vector2 p2 = nodos->nodo[fin].posicion;
        //DrawLineEx(p1, p2, 3, GREEN);//color verde para conecciones 
    //}
//}


void Dibujar_Fuente_C(ArregloFuentes_C *punt_datos)
{   
   //ciclo para impresion constante de todas las fuentes
    for (size_t i = 0; i < punt_datos->tamano; i ++ ){

	if(punt_datos->fuentes_C[i].rotacion == 0) {//esto representa a la version hozizontal, que ya habia
    		DrawLine(x - 60, y, x - 25, y, BLACK);
		DrawCircleLines(x, y, 25, BLACK);//ciculo central 
    		DrawLine(x - 10, y, x + 10, y, BLUE);//linea horizontal
    		DrawLine(x + 10, y, x, y - 10, BLUE);//inclinada superior
    		DrawLine(x + 10, y, x, y + 10, BLUE);//inclinada inferior
    		DrawLine(x + 25, y, x + 60, y, BLACK);
	}
	else {//esto es el cambio
    		DrawLine(x, y - 60, x, y - 25, BLACK);
    		DrawCircleLines(x, y, 25, BLACK);
    		DrawLine(x, y + 10, x, y - 10, BLUE);
    		DrawLine(x, y - 10, x - 8, y, BLUE);
    		DrawLine(x, y - 10, x + 8, y, BLUE);
    		DrawLine(x, y + 25, x, y + 60, BLACK);
	}
    //esto es para el texto de la fuente
        DrawText(punt_datos->fuentes_C[i].nombre, x - 12, y - 45, 20, BLACK);
        DrawText(punt_datos->fuentes_C[i].valor, x - 12, y + 25, 18, RED);

        //cambio de color si es seleccionado
        if (punt_datos->fuentes_C[i].seleccionado == true) {
		 if(punt_datos->fuentes_C[i].rotacion == 0) {//para permitir la rotacion
            		DrawLine(x - 60, y, x - 25, y, RED);
            		DrawCircleLines(x, y, 25, RED);
            		DrawLine(x - 10, y, x+10, y , RED);
            		DrawLine(x + 10, y, x , y - 10 , RED);
            		DrawLine(x + 10, y, x , y + 10 , RED);
            		DrawLine(x + 25, y, x + 60, y, RED);
		}
		else {//este agregado es para que rote
			DrawLine(x, y - 60, x, y - 25, RED);
			DrawCircleLines(x, y, 25, RED);
			DrawLine(x, y + 10, x, y - 10, RED);
        		DrawLine(x, y - 10, x - 8, y, RED);
        		DrawLine(x, y - 10, x + 8, y, RED);
			DrawLine(x, y + 25, x, y + 60, RED);
    		}
        	DrawText(punt_datos->fuentes_C[i].nombre, x - 12, y - 45, 20, BLUE);
        	DrawText(punt_datos->fuentes_C[i].valor, x - 12, y + 25, 18, BLUE);
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

//aca se agrega el codigo que permite la rotacion 
void Rotar_Fuente_C(ArregloFuentes_C *punt_datos) {
        for(size_t i = 0; i < punt_datos->tamano; i++) {
                if(punt_datos->fuentes_C[i].seleccionado) {
                        if(punt_datos->fuentes_C[i].rotacion == 0) {
                                punt_datos->fuentes_C[i].rotacion = 1; //mientras que aca se evalua si e>
                        }
                        else {
                                punt_datos->fuentes_C[i].rotacion = 0; //esto permite que siempre este e>
                        }
                        break;
                }
        }
}
//fin de agregado para rotar

void Mover_Fuente_C(ArregloFuentes_C *punt_datos)
{
    for (size_t i = 0; i < punt_datos->tamano; i++)
    {
        if (punt_datos->fuentes_C[i].seleccionado)
        {
            if (IsKeyDown(KEY_RIGHT))
            {
                punt_datos->fuentes_C[i].posicion.x += 5;
            }

            if (IsKeyDown(KEY_LEFT))
            {
                punt_datos->fuentes_C[i].posicion.x -= 5;
            }

            if (IsKeyDown(KEY_UP))
            {
                punt_datos->fuentes_C[i].posicion.y -= 5;
            }

            if (IsKeyDown(KEY_DOWN))
            {
            punt_datos->fuentes_C[i].posicion.y += 5;
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
	.rotacion = 0
    };

    snprintf(nodo.nombre, MAX_TEXTO_COMPONENTE, "Nodo");
    snprintf(nodo.valor, MAX_TEXTO_COMPONENTE, "%zu", punt_datos->tamano + 1);

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

void Dibujar_Nodo(ArregloNodos *punt_datos) {
//si bien la rotacion de un nodo es innecesaria en este momento, de cara a un nodo especial en el futurop, es mejor tenerlo listo
    for (size_t i = 0; i < punt_datos->tamano; i++) {
        int x = punt_datos->nodo[i].posicion.x;
        int y = punt_datos->nodo[i].posicion.y;

        if(punt_datos->nodo[i].rotacion == 0) {
            DrawCircle(x, y, 10, BLUE);
            DrawText(punt_datos->nodo[i].nombre, x - 20, y - 30, 20, BLACK);
            DrawText(punt_datos->nodo[i].valor, x - 1, y + 13, 18, BLACK);
        }
        else
        {
            // Reservado para futuras rotaciones en caso de un nodo especial
            DrawCircle(x, y, 10, BLUE);
            DrawText(punt_datos->nodo[i].nombre, x - 20, y - 30, 20, BLACK);
            DrawText(punt_datos->nodo[i].valor, x - 1, y + 13, 18, BLACK);
        }
        if (punt_datos->nodo[i].seleccionado) {
            DrawCircle(x, y, 10, RED);
            DrawText(punt_datos->nodo[i].nombre, x - 20, y - 30, 20, BLUE);
            DrawText(punt_datos->nodo[i].valor, x - 1, y + 13, 18, BLUE);
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

//determinacion de que el usuariop selecciono el nodo como tal 

//int Obtener_Nodo_Seleccionado(ArregloNodos *punt_datos) {
    //Vector2 mouse = GetMousePosition();//esto funciona con click derecho
    //for(size_t i = 0; i < punt_datos->tamano; i++) {
        //Rectangle caja = Caja_de_seleccion_Nodo(punt_datos->nodo[i]);
        //if(CheckCollisionPointRec(mouse,caja))
        //{
            //return i;
        //}
    //}
    //return -1;
//}


Rectangle Caja_de_seleccion_Nodo(Nodo Nodo){  //cajita de la fuente de corriente por si es seleccionado

    Rectangle caja = {Nodo.posicion.x - 20, Nodo.posicion.y -20, 30, 30}; 
    return caja; 
} 

//aca se agrega el codigo que permite la rotacion 
//esta funcion se agrega por el remoto caso que la forma del nodo sea especial y por tanto, rotabble
void Rotar_Nodo(ArregloNodos *punt_datos) {
        for(size_t i = 0; i < punt_datos->tamano; i++) {
                if(punt_datos->nodo[i].seleccionado) {
                        if(punt_datos->nodo[i].rotacion == 0) {
                                punt_datos->nodo[i].rotacion = 1; //mientras que aca se evalua si e>
                        }
                        else {
                                punt_datos->nodo[i].rotacion = 0; //esto permite que siempre este e>
                        }
                        break;
                }
        }
}
//fin de agregado para rotar

void Mover_Nodo(ArregloNodos *punt_datos)
{
    for (size_t i = 0; i < punt_datos->tamano; i++)
    {
        if (punt_datos->nodo[i].seleccionado)
        {
            if (IsKeyDown(KEY_RIGHT))
            {
                punt_datos->nodo[i].posicion.x += 5;
            }

            if (IsKeyDown(KEY_LEFT))
            {
                punt_datos->nodo[i].posicion.x -= 5;
            }

            if (IsKeyDown(KEY_UP))
            {
                punt_datos->nodo[i].posicion.y -= 5;
            }

            if (IsKeyDown(KEY_DOWN))
            {
            punt_datos->nodo[i].posicion.y += 5;
            }

            break;
        }
    }
}
