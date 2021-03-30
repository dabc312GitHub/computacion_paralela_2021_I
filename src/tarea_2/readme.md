# Pruebas sobre el comportamiento de la memoria caché: bucles anidados

El alumno debe realizar un informe en formato artículo (en Latex) donde la implementación, resultados y análisis de la ejecución para los siguientes problemas:

- Implementar en C/C++ la multiplicación de matrices clásica, la versión de tres bucles anidados y evaluar su desempeño considerando diferentes tamaños de matriz.
  
  ```cpp
  #define MAX_i 400
  #define MAX_k 500
  #define MAX_j 600
  
  double A[MAX_i][MAX_k], B[MAX_k][MAX_j], res[MAX_i][MAX_j];
  
  void multiplicacion_clasica() {
      for (size_t i = 0; i < MAX_i; i++) {
          for (size_t j = 0; j < MAX_j; j++) {
              for (size_t k = 0; k < MAX_k; k++) {
                  res[i][j] += A[i][k] * B[k][j];
              }
          }
      }
  }
  ```

- Implementar la version por bloques (investigar en in|ternet), seis bloques anidados, evaluar su desempeño y compararlo con la multiplicación de matrices clásica.
  
  ```cpp
  void multiplicacion_bloques() {
      int bsize = max(MAX_i, MAX_j);
  
      for (int i = 0; i < MAX_i; i+=bsize) {
          for (int j = 0; j < MAX_j; j=+bsize) {
              for (int k = 0; k < MAX_k; k=+bsize) {
                  for (size_t ii = i; ii < min(i+bsize, MAX_i); ii++) {
                      for (size_t jj = j; jj < min(j+bsize, MAX_j); jj++) {
                          for (size_t kk = k; kk < min(k+bsize, MAX_k); kk++) {
                              res[ii][jj] += A[ii][kk] * B[kk][jj];
                          }
                      }
                  }
              }
          }
      }
  }
  ```

- Ejecutar ambos algoritmos paso a paso, y analisar el movimiento de datos entre la memoria principal y la memoria cache. Hacer una evaluación de acuerdo a la complejidad algoritmica.

- Ejecutar ambos algoritmos utilizando las herramientas valgrind y kcachegrind para obtener una evaluación mas precisa de su desempeño en términos de cache misses.

- <mark>**IMPORTANTE**: Todo informe debe tener un ENLACE a un repositorio en linea (github.com por ejemplo) donde se encuentre el código fuente de su trabajo.</mark>

## Multiplicación de matrices bloqueadas:

https://malithjayaweera.com/2020/07/blocked-matrix-multiplication/

#### ¿Por qué es importante la multiplicación de matrices?

Esta es usada en muchas aplicaciones científicas y recientemente ha sido usado como un reemplazo para convoluciones en redes neuronales profundas(DNNs) usando la operación im2col.

#### Almacenamiento en matriz

Hay 2 maneras de almacenar una matriz densa en memoria. Una matriz densa es donde todo/significante porcentaje (>40%) de los elementos son no ceros.Las matrices dispersas pueden ser almacenados en espacio de manera eficiente explotando características de cero. 

colocar aqui la imagen

En la columna de orden mayor, los valores son almacenados secuencialmente siguiendo el orden de las columnas. Parecido, en fila mayor, los valores estan almacenados secuencialmente siguiendo el orden de las filas. El orden es importante debido a como estos valores son almacenados en memoria. Para acceso eficiente, es vital que los algoritmos sean conscientes del patrón de almacenamiento subyacente.

#### Modelo de optimización de memoria simple

Asumiremos 2 niveles de memoria para simplificar: rápido y lento. Puedes pensar como estos son la RAM y un nivel de cache. Inicialmente la data es almacenado en memoria lenta. Definiremos lo siguiente.

- m = número de elementos en memoria movidos entre memoria lenta y rápida

- $t_m$= tiempo por operación en memoria lenta

- f = número de operaciones aritméticas

- $t_f$ = tiempo por operación aritmética

- q = f/m (número promedio de fracasos por acceso a memoria lento)

El factor **q** es también conocido como la "intensidad computacional" y es vital para la eficiencia del algoritmo debido a que el acceso por memoria lenta nosotros intentamos hacer más operaciones aritméticas.

Mínimo tiempo computación posible = $t_f * f$ 

(asumiendo que la memoria pedida ya está en memoria rápida)

Tiempo de computación actual = costo computacional + costo de data tomada

= $f * t_f + m * t_m$

= $f * t_f (1 + (m * t_m) / (f * t_f))$

= $f * t_f (1 + t_m / t_f * 1/q)$ -- ecuación (1)

$t_m / t_f$ es conocido como balance de maquina  y es importante asegurar la eficiencia de la máquina. Por lo tanto, observamos que la eficiencia de memoria depende de ambos tanto balance de maquina y la intensidad computacional. Con valores **q** altos, podemos lograr el mínimo tiempo posible de ejecución teórico.

Lograr la mita del pico de velocidad
