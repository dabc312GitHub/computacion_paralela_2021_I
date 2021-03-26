# Pruebas sobre el comportamiento de la memoria caché: bucles anidados

En la imagen se puede ver que el first pair es más rápido debido a que se
obtiene el valor avanzando por filas en una columna, en cambio el second pair
es al revés. Este es un juego de ı́ndices que se toma en consideración para
realizar las operaciones correspondientes.

![]()

Imagen 1:  Ejemplo visual para un valor MAX de 4

| valor de MAX | firstPair     | secondPair     |
| ------------ | ------------- | -------------- |
| 500          | 924 microsec  | 1370 microsec  |
| 1000         | 6574 microsec | 12799 microsec |
| 1500         | 9578 microsec | 18810 microsec |

Tabla 1: Resultados de comparación en microsegundos
