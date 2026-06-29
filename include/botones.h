#ifndef BOTONES_H
#define BOTONES_H

#include "raylib.h"
#include <stdbool.h>

//esta funcion retorna un booleano pues se necesita parra dibujar el componente si se clickea el boton 
bool ButtonClicked(Rectangle boton);

//esta funcion es general para dibujar cualquier boton, vease que es clave darle una variable de tipo rectangle pues contiene lo necesario
void Dibujar_boton(Rectangle boton_general, const char* texto);

#endif