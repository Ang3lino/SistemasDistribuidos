
all: transmisor1 receptor1

DatagramPacket.o: DatagramPacket.cpp
	g++ -Wall -c -g DatagramPacket.cpp 
DatagramSocket.o: DatagramSocket.cpp
	g++ -Wall -c -g DatagramSocket.cpp 
MulticastSocket.o: MulticastSocket.cpp
	g++ -Wall -c -g MulticastSocket.cpp 

transmisor1: DatagramPacket.o DatagramSocket.o MulticastSocket.o transmisor1.o
	g++ DatagramPacket.o DatagramSocket.o MulticastSocket.o transmisor1.o -o transmisor1 -g3

receptor1: DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor1.o
	g++ DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor1.o -o receptor1 -g3

clean: 
	rm *.o transmisor1 receptor1

