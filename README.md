# Proyecto_Final_Plataformas_G1
Proyecto final: DC Simulator (Simple Edition)

## Proyecto final: DC Simulator (Simple Edition)
# Simulador de Circuitos DC
Proyecto Final del curso de Programación I.

Aarón Madrigal - C14373
Brayan Sanchez Chavarria - C37283
Theo
Este proyecto consiste en un simulador gráfico de circuitos eléctricos en corriente directa (DC), desarrollado en lenguaje C utilizando la biblioteca Raylib. El programa permite construir circuitos mediante una interfaz gráfica intuitiva con el usuario. Esta edición es simplificada y no cuenta con análsis de tensión, corriente y potencia.

# Dependencias

Para compilar el proyecto es necesario tener instalado:

- GCC
- Make
- Raylib
- OpenGL

## Operaciones a tener en cuenta

 - Click derecho + C permite la union de los componentes y los nodos
 - Click derecho sobre componente para generar el primer nodo, repetir para el segundo
 - Dezplazar el componente en pantalla mediante click derecho sostenido
 - Generar un componente mediante el click derecho sobre la casilla respectiva
 - Click derecho + R para totar
 - Con tecla E permite la edicion de valores para la division. Con TAB permite se cambia de campo en la edicion de valores. Con ENTER para guardar los cambios.
 - Eliminar un componente se selecciona, tras cambiar de color, precione en eliminar componente
 - La union entre componente y nodo opera por colores, el rojo representa al resistor, el azul la fuente de tension y el verde la fuente de corriente

 
## Compilación

En Ubuntu puede instalarse Raylib siguiendo la documentación oficial presente en repositorio de Raylib en Github.


# Compilación

Para compilar:

```bash
make clean
make
```

Para ejecutar:

```bash
make run
```

Para limpiar el ejecutable:

```bash
make clean
```

Para revisar fugas de memoria con Valgrind (Requiere instalar Valgrind previamente con apt en Ubuntu):

```bash
make memcheck
```

# Instrucciones de uso

1. Ejecute el programa usando el comando sugerido.
2. Utilice la barra de herramientas para agregar componentes electricos a la plantilla de trabajo.
3. Seleccione un componente con clic izquierdo.
4. Muévalo utilizando las flechas del teclado (puede mantenerlo apretado para moverlo de manera continua).
5. Elimine y rote componentes mediante el botón correspondiente.
6. Una vez seleccionado un componente, presione la tecla E para editar sus caracteristicas.
7. Integre todas los componentes necesarios antes de conectarlos
8. (instruccion para conectar los componentes)

# Integrantes

- Theo Wang Lizarme - C5L093
- Aarón Madrigal Marín - C14373
- Bryan Sánchez Chavarría - C37283

# Características implementadas

Actualmente el proyecto cuenta con:

- Interfaz gráfica desarrollada con Raylib.
- Barra de herramientas.
- Cuadrícula (Grid) para posicionamiento.
- Creación dinámica de componentes.
- Resistores.
- Fuentes de voltaje.
- Fuentes de corriente.
- Selección de componentes.
- Movimiento mediante teclado.
- Eliminación de componentes.
- Manejo de memoria mediante arreglos dinámicos.


# Estructura del proyecto

```
Proyecto
│
├── include/
│   ├── botones.h
│   ├── componentes.h
│   └── simulador.h
│
├── src/
│   ├── botones.c
│   ├── componentes.c
│   ├── simulador.c
│   └── main.c
│
├── Makefile
├──.gitignore
└── README.md

```

