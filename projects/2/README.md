
# Animación de meteoros
### Ángel López Manríquez
### 4CM1

**Descripción**: el proyecto consiste en hacer una animación de $n$ meteoros, cada meteoro deberá rotar y rebotar. Como algo extra, cada que  un meteoro rebota su contorno cambia de color.

## Dependencias 
La biblioteca X11, gcc, g++ y makefile, la cual puede ser instalada ejecutando
`
sudo apt install libx11-dev gcc g++ make
`
## Instrucciones de ejecución
En el directorio *src*, ecutar 
`make`
Se creara un binario de nombre *a.out*, se le deberá pasar por linea de comandos cuantos meteoros se desean en la animación. **En caso de no pasarle este argumento se mostrar 
```./a.out [N_ASTEROIDES]```
y no se mostrara ninguna animación.** El programa se probo en Linux Mint y Deepin.

Si desea eliminar los binarios haga `make clean`.

