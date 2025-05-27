# 🔥 Simulación de difusion de calor en una superficie 2D
 
Proyecto final de la asignatura **Arquitectura de Computadores**, que implementa una simulacion de difusion de calor en una placa metálica bidimenional cuadrada mediante:

- ❕ Versión Secuencial (C).
- ❕ Versión Paralela con OpenMP.

---

## 📌 Descripcion del problema

Se simula la evolucion térmica en una matriz `N x N`, donde:
- Los bordes están fijos a `100ºC`.
- El interior comienza a `0ºC`.
- En acada iteracion, cada celda se actualiza con el promedio de sus 4 vecinas (arriba, abajo, izquierda y derecha).
- La simulacion finaliza cuando el cambio máximo de temperatura cae por debajo de un umbral o se alcanza el número máximo de iteraciones.

---

## 🛠️ Tecnologias utilizadas

- Lenguaje: C (estándar 11)
- Sistema operativo: macOS (Apple Silicon)
- Compilador: Clang con soporte en OpenMP (`libomp`)
- Entorno de desarrollo: CLion + CMake
- Paralelismo: OpenMP

---

## ⚠️ Nota sobre compilación en macOS

En lugar de `gcc -fopenmp`, se utilizó Clang con OpenMP vía `libomp` por incompatibilidad de GCC en los SDKs de Apple.

---

## 👩‍💻 Autores

- Sira González-Madroño García
- Miriam Blanco Ponce

---

## 📄 Memoria

La explicacion detallada de la solucion, análisis de resultados y comparacion entre versiones se encuentra en el documento `Memoria práctica final arquitectura.pdf` incluido en este repositorio.
