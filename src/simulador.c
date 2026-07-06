#include "botones.h"
#include "componentes.h"
#include "simulador.h"

#include <raylib.h>
#include <stdio.h>
#include <string.h>

//----------Seccion de posicones y dimensiones de componentes(dibujo del componente y su boton asociado)-----------------

//====== Para los Componentes ======

ArregloResistores arreglo_R; 
ArregloFuentes_T arreglo_F_T;
ArregloFuentes_C arreglo_F_C;
ArregloNodos arreglo_nodo;

//Nodos seleccionados para las conecciones
int nodo_inicio_seleccionado = -1;
int nodo_fin_seleccionado = -1;
//deben estar declaradas fuera de cualquier funcion 

//este boton si es estatico y sirve siempre 
static Rectangle resistor_boton = {20, 20, 180, 45};
static Rectangle fuente_T_boton = {20, 80, 180, 45};
static Rectangle fuente_C_boton = {220, 20, 180, 45};
static Rectangle nodo_boton = {220, 80, 180, 45};
static Rectangle rotar_boton = {420, 20, 150, 45};
static Rectangle eliminar_boton = {420, 80, 150, 45};

//variables de edicion

typedef enum{
    EDITAR_NINGUNO,
    EDITAR_RESISTOR,
    EDITAR_FUENTE_T,
    EDITAR_FUENTE_C,
    EDITAR_NODO
} TipoEdicion;

static bool modo_edicion = false;
static bool editando_valor = false;
static TipoEdicion tipo_edicion = EDITAR_NINGUNO;
static size_t indice_edicion = 0;

static char buffer_nombre[MAX_TEXTO_COMPONENTE];
static char buffer_valor[MAX_TEXTO_COMPONENTE];


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

static void AgregarCaracter(char *texto, int caracter){
    size_t longitud = strlen(texto);

    if (longitud < MAX_TEXTO_COMPONENTE - 1){

        texto[longitud] = (char)caracter;
        texto[longitud + 1] = '\0';
    }
}

static void BorrarCaracter(char *texto){
    size_t longitud = strlen(texto);

    if (longitud > 0){
        texto[longitud - 1] = '\0';
    }
}

static bool Cargar_Componente_Seleccionado(void){
    for (size_t i = 0; i < arreglo_R.tamano; i++){
        if (arreglo_R.resistores[i].seleccionado){
            tipo_edicion = EDITAR_RESISTOR;
            indice_edicion = i;
            strcpy(buffer_nombre, arreglo_R.resistores[i].nombre);
            strcpy(buffer_valor, arreglo_R.resistores[i].valor);
            return true;
        }
    }


    for (size_t i = 0; i < arreglo_F_T.tamano; i++){
        if (arreglo_F_T.fuentes_T[i].seleccionado){
            tipo_edicion = EDITAR_FUENTE_T;
            indice_edicion = i;
            strcpy(buffer_nombre, arreglo_F_T.fuentes_T[i].nombre);
            strcpy(buffer_valor, arreglo_F_T.fuentes_T[i].valor);
            return true;
        }
    }


    for (size_t i = 0; i < arreglo_F_C.tamano; i++){
        if (arreglo_F_C.fuentes_C[i].seleccionado){
            tipo_edicion = EDITAR_FUENTE_C;
            indice_edicion = i;
            strcpy(buffer_nombre, arreglo_F_C.fuentes_C[i].nombre);
            strcpy(buffer_valor, arreglo_F_C.fuentes_C[i].valor);
            return true;
        }
    }


    for (size_t i = 0; i < arreglo_nodo.tamano; i++){
        if (arreglo_nodo.nodo[i].seleccionado){
            tipo_edicion = EDITAR_NODO;
            indice_edicion = i;
            strcpy(buffer_nombre, arreglo_nodo.nodo[i].nombre);
            strcpy(buffer_valor, arreglo_nodo.nodo[i].valor);
            return true;
        }
    }

    return false;
}

static void Guardar_Edicion_Componente(void){
    switch (tipo_edicion){
        case EDITAR_RESISTOR:
            strcpy(arreglo_R.resistores[indice_edicion].nombre, buffer_nombre);
            strcpy(arreglo_R.resistores[indice_edicion].valor, buffer_valor);
            break;

        case EDITAR_FUENTE_T:
            strcpy(arreglo_F_T.fuentes_T[indice_edicion].nombre, buffer_nombre);
            strcpy(arreglo_F_T.fuentes_T[indice_edicion].valor, buffer_valor);
            break;


        case EDITAR_FUENTE_C:
            strcpy(arreglo_F_C.fuentes_C[indice_edicion].nombre, buffer_nombre);
            strcpy(arreglo_F_C.fuentes_C[indice_edicion].valor, buffer_valor);
            break;


        case EDITAR_NODO:
            strcpy(arreglo_nodo.nodo[indice_edicion].nombre, buffer_nombre);
            strcpy(arreglo_nodo.nodo[indice_edicion].valor, buffer_valor);
            break;

        default:
            break;
    }
}

static void Actualizar_Modo_Edicion(void){
    int caracter;

    if (IsKeyPressed(KEY_TAB)){

        editando_valor = !editando_valor;
    }

    if (IsKeyPressed(KEY_BACKSPACE)){
        if(editando_valor){
            BorrarCaracter(buffer_valor);
        }
        else {
            BorrarCaracter(buffer_nombre);
        }
    }

    caracter = GetCharPressed();

    while (caracter > 0){
        if ((caracter >= 32) && (caracter <= 125)){
            if (editando_valor){
                AgregarCaracter(buffer_valor, caracter);
            }
            else {
                AgregarCaracter(buffer_nombre, caracter);
            }
        }

        caracter = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER)){
        Guardar_Edicion_Componente();

        modo_edicion = false;
        tipo_edicion = EDITAR_NINGUNO;
        editando_valor = false;

        printf("Cambios guardados correctamente.\n");
    }

    if (IsKeyPressed(KEY_ESCAPE)){
        modo_edicion = false;
        tipo_edicion = EDITAR_NINGUNO;
        editando_valor = false;

        printf("Edicion cancelada.\n");
    }
}


void ActualizarSimulador() {

	//actualizacion para lector de seleccion en nodo 
	if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {//con el primer click derecho, se establece el primer nodo
    		int nodo = Obtener_Nodo_Seleccionado(&arreglo_nodo);
    		if(nodo != -1) {
        		if(nodo_inicio_seleccionado == -1) {
            			nodo_inicio_seleccionado = nodo;
			}
		}
        	else {//con un segundo click derecho, selecciona el nodo final. 
            		nodo_fin_seleccionado = nodo;
        	}
    	}

	//se agrega la deteccion mediante la tecla C de que se desea conectar el nodo de un componente a otro nodo
	//para los resistores
	if(IsKeyPressed(KEY_C)) {
    		for(size_t i = 0; i < arreglo_R.tamano; i++) {
        		if(arreglo_R.resistores[i].seleccionado) {
            			Conectar_Resistor(&arreglo_R, i, nodo_inicio_seleccionado, nodo_fin_seleccionado);
            			printf("Resistor conectado\n");
            			break;
        		}
    		}
	//para la fuente de tension 
    		for(size_t i = 0; i < arreglo_F_T.tamano; i++) {
        		if(arreglo_F_T.fuentes_T[i].seleccionado) {
            			Conectar_Fuente_T(&arreglo_F_T, i, nodo_inicio_seleccionado, nodo_fin_seleccionado);
            			printf("Fuente de tension conectada\n");
            			break;
        		}
    		}
	//para la cuente de corriente
    		for(size_t i = 0; i < arreglo_F_C.tamano; i++) {
        		if(arreglo_F_C.fuentes_C[i].seleccionado) {
            			Conectar_Fuente_C(&arreglo_F_C, i, nodo_inicio_seleccionado, nodo_fin_seleccionado);
            			printf("Fuente de corriente conectada\n");
            			break;
        		}
    		}
	}

    //revisar primero si esta en modo edicion
    if (modo_edicion){
        Actualizar_Modo_Edicion();
        return;
    }

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


    if(ButtonClicked(rotar_boton) == true){ //implementa la rotacion de los componentes existentes con el avizo actualizado 
    	Rotar_Resistor(&arreglo_R);
 	Rotar_Fuente_T(&arreglo_F_T);
    	Rotar_Fuente_C(&arreglo_F_C);
    	Rotar_Nodo(&arreglo_nodo);
        printf("Componente rotado");
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

    if (IsKeyPressed(KEY_E)){

        if (Cargar_Componente_Seleccionado()){

            modo_edicion = true;
            editando_valor = false;
            printf("Editando componente. TAB cambia campo, ENTER guarda, ESC cancela.\n");
        }
        else {
            printf("Seleccione un componente antes de editar.\n");
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

    if (modo_edicion){
        DrawText("EDITANDO COMPONENTE", 910, 55, 18, BLUE);

        DrawText("Nombre:", 910, 85, 18, BLACK);
        DrawText(buffer_nombre, 1000, 85, 18, editando_valor ? DARKGRAY : BLUE);

        DrawText("Valor:", 910, 115, 18, BLACK);
        DrawText(buffer_valor, 1000, 115, 18, editando_valor ? BLUE : DARKGRAY);
    }


    Imprimir_Grid();

    //----------Botones para el toolbar(FALTAN MAS)------
    Dibujar_boton(resistor_boton, "Agregar R");
    Dibujar_boton(fuente_T_boton, "Agregar F-T");
    Dibujar_boton(fuente_C_boton, "Agregar F-C");
    Dibujar_boton(nodo_boton, "Agregar N");
    Dibujar_boton(rotar_boton, "Rotar Comp");
    Dibujar_boton(eliminar_boton, "Eliminar");

    //dibujado de los componentes, ahora solo se necesita una funcion que en realidad es un loop
    Dibujar_Conexiones_Resistores(&arreglo_R, &arreglo_nodo);
    Dibujar_Conexiones_Fuente_T(&arreglo_F_T, &arreglo_nodo);
    Dibujar_Conexiones_Fuentes_C(&arreglo_F_C, &arreglo_nodo);

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
