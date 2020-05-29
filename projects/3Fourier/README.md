
# Proyecto 3 
## Gratificador de las sumas parciales crecientes de Fourier para una función particular
### Diseño de sistemas distribuidos
### Alumno: Ángel López Manríquez
### Grupo: 4CM1

Descripción: el proyecto consiste en hacer un graficador en Java el cual recibirá un conjunto de puntos $\{x_i, y_i\}_{i=0}^n$ a través del protocolo no orientado a conexión y los graficara tan pronto se haya recibido el conjunto de puntos. El generador de puntos tiene que estar escrito en C++ y se encargara de generar las sumas parciales de la serie de Fourier para una función $f(t)$ particular.

**Ambos programas están diseñados para poder ser ejecutados tanto como en Linux como en Windows 10**. Java por defecto hace esto ya que es interoperable, por otro lado los sockets de C no y se tuvo que hacer distinción de en que sistema operativo se corre el sistema a través de las directivas de pre procesamiento. En un principio se indico que el generador tenia que correr en Windows 10.

## Instrucciones de ejecución
El programa se probo con C++ versión 11, Makefile, Java 8 y JavaFx en windows 10. Compile y ejecute en el orden indicado.
1. Servidor
Una vez estando en el directorio *server* ejecutar 
`make`
Se mostrar una grafica cuadriculada sin ningun punto, esperando una conexion.
2. Cliente
Una vez estando en el directorio *client* ejecutar 
`make`
`generator.exe`

Se mostrara por pantalla en formato hexadecimal los primeros bytes enviados al servidor y la graficadora los mostrara como vayan llegando.

2020.