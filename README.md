
# Proyecto final: DC Simulator (Simple Edition)

# Simulador de Circuitos DC
Proyecto Final del curso de Programación I.

- Aarón Madrigal - C14373
- Brayan Sanchez Chavarria - C37283
- Theo Wang Lizarme - C5L093

Este proyecto consiste en un simulador gráfico de circuitos eléctricos en corriente directa (DC), desarrollado en lenguaje C utilizando la biblioteca Raylib. El programa permite construir circuitos mediante una interfaz gráfica intuitiva con el usuario. Esta edición es simplificada y no cuenta con análsis de tensión, corriente y potencia.

# Dependencias

Para compilar el proyecto es necesario tener instalado:

- GCC
- Make
- Raylib
- OpenGL
 
## Compilación

En Ubuntu puede instalarse Raylib siguiendo la documentación oficial presente en repositorio de Raylib en Github.


# Compilación

Para compilar:

```bash
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
6. Una vez seleccionado un componente, presione la tecla E para editar sus caracteristicas. TAB para moverse de caracteristica. Enter para confirmar cambios
7. Integre todas los componentes necesarios antes de conectarlos
8. Seleccione el componente a concetar. Cuando se vea en rojo, haga CLICK DERECHO sobre el nodo al que quiera conectar la primera terminal y CLICK DERECHO nuevamente sobre el otro nodo para crear los cables.

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
- Conexion visual de los componentes.


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

