# Pruebas sobre el comportamiento de la memoria caché: bucles anidados

En la imagen se puede ver que el first pair es más rápido debido a que se
obtiene el valor avanzando por filas en una columna, en cambio el second pair
es al revés. Este es un juego de ı́ndices que se toma en consideración para
realizar las operaciones correspondientes.

![Alt text](https://github.com/dabc312GitHub/computacion_paralela_2021_I/blob/master/src/tarea_1/assets/Captura%20de%20pantalla%202021-03-25%20182447.png)

Imagen 1:  Ejemplo visual para un valor MAX de 4

| valor de MAX | firstPair     | secondPair     |
| ------------ | ------------- | -------------- |
| 500          | 924 microsec  | 1370 microsec  |
| 1000         | 6574 microsec | 12799 microsec |
| 1500         | 9578 microsec | 18810 microsec |

Tabla 1: Resultados de comparación en microsegundos

## Cache y programas: un ejemplo

Es importante recordar que trabajar con la CPU cache are controlled by the system y nosotros, los programadores, no directamente determinan cual data y cual instrucciones estan en la cache. Sin embargo, sabiendo el principio de localidad espacio y temporal que nos permite tener algo de control indirecto sobre la cache. Por ejemplo, el lenguaje C almacena arreglos de dos dimensiones en orden de **"la fila mayor"**. Asi que, aunque pensemos de un arreglo de 2 dimensiones como un bloque rectangular, la memoria es efectivamente un enorme arreglo unidimensional. Asi que en un almacenamiento mayor de filas, almacenamos primero la fila 0, luego la fila 1 y asi sucesivamente. En los siguientes segmentos de codigo, esperariamos el primer par de bucles anidados para tener una mejor performance que el segundo par, debido a que esta accediendo a la data en el arreglo de 2 dimensiones en bloques contiguos.

```cpp
double A[MAX][ MAX], x [MAX], y[ MAX];
. . .
/∗ Initialize A and x, assign y = 0 ∗/
. . .
/∗ First pair of loops ∗/
for (i = 0; i < MAX ; i++) 
    for (j = 0; j < MAX ; j++) 
        y[i] += A[ i][j] * x[j];  
. . .
/∗ Assign y = 0 ∗/
. . .
/∗ Second pair of loops ∗/
for (j = 0; j < MAX ; j++)
    for (i = 0; i < MAX ; i++)
        y[i] += A[ i][j] * x[j];
```

Para entender mejor esto, supongamos que el valor de MAX es 4 y los elementos de **A** son almacenados en memoria como indica la siguiente tabla.

| Cache Line |         | Elemens | of      | **A**   |
| ---------- | ------- | ------- | ------- |:-------:|
| 0          | A[0][0] | A[0][1] | A[0][2] | A[0][3] |
| 1          | A[1][0] | A[1][1] | A[1][2] | A[1][3] |
| 2          | A[2][0] | A[2][1] | A[2][2] | A[2][3] |
| 3          | A[3][0] | A[3][1] | A[3][2] | A[3][3] |

Asi que, por ejemplo, A[0][1] esta almacenado inmediatamente despues de A[0][0] y A[1][0] es almacenado inmediatamente despues de A[0][3].

Supongamos que ninguno de los elementos de A están en la cache cuando cada par de bucles inicia ejecutando. Ahora supongamos que una linea de cache consiste de 4 elementos de A[0][0] es el primer elemento de una linea de cache. Finalmente, supondremos que la cache mapeado de forma directa y solo puede almacenar 8 elementos de A, o dos líneas de cache. (no nos preocuparemos por **x** o **y**)

Ambos pares de bucles intentan acceder primero A[0][0]. Debido a que no está en la cache, esto resultará en una cache miss, y el sistema leerá la línea consistiendo de la primera línea de A, A[0][0], A[0][1], A[0][2], A[0][3], en la cache. El primer par de bucles entonces son accesados A[0][1], A[0][2], A[0][3], todo de lo cual están en la cache, y el siguiente miss en el primer par de loops ocurrira cuando el código acceda a A[1][0]. Continuando en esta perspectiva, observamos que el primer par de bucles resultará en un total de 4 misses cuando acceda a los elementos de A, uno por cada fila. Notar que debido a nuestra hipotética cache solo puede almacenar 2 líneas de 8 elementos de A, cuando leemos el primer elemento de la fila 2 y el primer elemento de la fila 3, una de las líneas que ya está en la cache tendrá que ser retirado de la cache, pero una vez que una línea es retirada, el primer par de bucles no necesitarán acceder a los elementos de esa líena de nuevo.

Después de leer la primera fila en la cache, el segundo par de bucles entonces necesita acceder A[1][0], A[2][0], A[3][0], ninguno de los cuales estan en la cache. Asi que los siguientes 3 accesos de A tambien resultaran en misses. Mas aún, debido que la cache es pequeña, la lecutra de A[2][0] y A[3][0] requeriran  que las líneas en la cache ya esten rechazadads. Desde que A[2][0] es almacenado en cache linea 2, leendo su línea evitará la línea 0, y leendo A[3][0] evitará la línea 1. Después de finalizar el primer pase a travs del bucle exterior, necesitaremos en la siguiente acceder a A[0][1], el cual es evitado con el resto de la primera fila. Asi que observamos que cada vez que leemos un elemento de A, tendremos un miss, y el segundo par de bucles resulta en 16 misses.

Asi que, esperamos que el primer par de bucles anidados a ser mucho más rápido que el segundo. De hecho, si ejecutamos el código en uno de nuestros sistemas con MAX = 1000, el primer par de bucles anidados es aproximadamente 3 veces más rápido que el segundo par.
