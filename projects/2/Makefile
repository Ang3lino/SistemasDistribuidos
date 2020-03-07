
compile: gfx.o animacion.o IrregularPolygon.o Coordenada.o
	g++ gfx.o animacion.o Coordenada.o IrregularPolygon.o -lX11 -Wall
IrregularPolygon.o: IrregularPolygon.cpp
	g++ IrregularPolygon.cpp -c
Coordenada.o: Coordenada.cpp
	g++ Coordenada.cpp -c
gfx.o: gfx.c 
	gcc gfx.c -c
animacion.o: animacion.cpp
	g++ animacion.cpp -c 
clear:
	rm *\.o 
	rm a.out 

