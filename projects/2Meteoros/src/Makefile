
compile: gfx.o animacion.o IrregularPolygon.o Coordenada.o Ellipse.o
	g++ gfx.o animacion.o Coordenada.o IrregularPolygon.o Ellipse.o -lX11 -Wall
IrregularPolygon.o: IrregularPolygon.cpp
	g++ IrregularPolygon.cpp -c
Ellipse.o: Ellipse.cpp
	g++ Ellipse.cpp -c
Coordenada.o: Coordenada.cpp
	g++ Coordenada.cpp -c
gfx.o: gfx.c 
	gcc gfx.c -c
animacion.o: animacion.cpp
	g++ animacion.cpp -c 
clear:
	rm *\.o 
	rm a.out 

