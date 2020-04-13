
cliente: cliente.o Solicitud.o PaqueteDatagrama.o SocketDatagrama.o
	g++ -g3 -Wall cliente.o Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -o cliente
cliente.o: cliente.cpp
	g++ -c -g3 -Wall cliente.cpp
Solicitud.o: Solicitud.cpp Solicitud.h
	g++ -c -g3 -Wall Solicitud.cpp 
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
	g++ -c -g3 -Wall SocketDatagrama.cpp 
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ -c -g3 -Wall PaqueteDatagrama.cpp 

clean:
	rm *.o
	rm cliente
	rm servidor

servidor: servidor.o Respuesta.o PaqueteDatagrama.o SocketDatagrama.o
	g++ -g3 -Wall servidor.o Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -o servidor
servidor.o: servidor.cpp 
	g++ -c -g3 -Wall servidor.cpp
Respuesta.o: Respuesta.cpp Respuesta.h
	g++ -c -g3 -Wall Respuesta.cpp 
