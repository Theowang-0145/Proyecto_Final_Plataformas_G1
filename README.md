# Proyecto_Final_Plataformas_G1
Proyecto final: DC Simulator (Simple Edition)

## Proyecto final: DC Simulator (Simple Edition)

Proyecto desarrollado en lenguaje C utilizando la biblioteca Raylib para el curso de Programación Bajo Plataformas Abiertas.

Aarón Madrigal - C14373
Brayan
Theo

## Descripción

Este programa permite construir circuitos eléctricos esquemáticos mediante una interfaz gráfica interactiva. El usuario puede agregar componentes como resistencias, fuentes independientes de tensión y fuentes independientes de corriente, conectarlos entre sí y visualizar sus valores eléctricos en pantalla.

## Funcionalidades principales

- Agregar resistencias.
- Agregar fuentes independientes de tensión.
- Agregar fuentes independientes de corriente.
- Mover componentes dentro del área de trabajo.
- Conectar componentes mediante nodos.
- Mostrar valores eléctricos en pantalla:
  - Voltios para fuentes de tensión.
  - Amperios para fuentes de corriente.
  - Ohmios para resistencias.
- Visualizar el circuito de forma esquemática.

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

```bash
make clean
make
make run
