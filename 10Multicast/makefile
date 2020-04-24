
all: transmisor receptor

DatagramPacket.o: DatagramPacket.cpp
	g++ -Wall -c -g DatagramPacket.cpp 
DatagramSocket.o: DatagramSocket.cpp
	g++ -Wall -c -g DatagramSocket.cpp 
MulticastSocket.o: MulticastSocket.cpp
	g++ -Wall -c -g MulticastSocket.cpp 
transmisor.o: transmisor.cpp
	g++ -Wall -c -g transmisor.cpp
receptor.o: receptor.cpp
	g++ -Wall -c -g receptor.cpp

transmisor: DatagramPacket.o DatagramSocket.o MulticastSocket.o transmisor.o
	g++ DatagramPacket.o DatagramSocket.o MulticastSocket.o transmisor.o -o transmisor -g3

receptor: DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor.o
	g++ DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor.o -o receptor -g3

clean: 
	rm *.o transmisor receptor