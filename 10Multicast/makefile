
all: transmisor1 receptor1 transmisor2 receptor2

DatagramPacket.o: DatagramPacket.cpp
	g++ -Wall -c -g DatagramPacket.cpp 
DatagramSocket.o: DatagramSocket.cpp
	g++ -Wall -c -g DatagramSocket.cpp 
MulticastSocket.o: MulticastSocket.cpp
	g++ -Wall -c -g MulticastSocket.cpp 

transmisor2.o: transmisor2.cpp
	g++ -Wall -c -g transmisor2.cpp 
receptor2.o: receptor2.cpp
	g++ -Wall -c -g receptor2.cpp 
transmisor1: DatagramPacket.o DatagramSocket.o MulticastSocket.o transmisor1.o
	g++ DatagramPacket.o DatagramSocket.o MulticastSocket.o transmisor1.o -o transmisor1 -g3 -Wall
receptor1: DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor1.o
	g++ DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor1.o -o receptor1 -g3 -Wall

transmisor2: DatagramPacket.o DatagramSocket.o MulticastSocket.o transmisor2.o
	g++ DatagramPacket.o DatagramSocket.o MulticastSocket.o transmisor2.o -o transmisor2 -g3 -Wall
receptor2: DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor2.o
	g++ DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor2.o -o receptor2 -g3 -Wall


clean: 
	rm *.o transmisor2 receptor2 transmisor1 receptor1

