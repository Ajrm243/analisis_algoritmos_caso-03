# analisis_algoritmos_caso-03
Caso 03 del curso
María José Porras Maroto 2019066056
Adrián Ramírez Mattey 2020239249

## Selección || Voraz

* N = Vector de paths filtrados según color 
* Etapas = Recorrer cada uno de los paths
* Óptimo Local = Sublista generada por las coincidencias de los puntos del usuario
* Óptimo Global = Lista con todos los paths seleccionados

## Enrutamiento  || Divide y Vencerás

* N = Vector con los paths generados en selección
* Sub Problemas = Análisis de los puntos de intersección de cada path
* Conquer = Calcular y asignar una única vez los movimientos lineales que seguirán los paths iguales
* Combine = Ordena la lista de paths seleccionados con la asignación ya realizada de movimientos

## Generación  || Programación Dinámica

* N = Vector con los paths generados en enrutamiento
* Sub Problemas = Análisis de los puntos de movimiento del path por frame a generar
* Fases = Cada uno de los frames de la animación.