all: receptor emisor

DatagramPacket.o: DatagramPacket.cpp
	g++ -Wall -c -g DatagramPacket.cpp 
DatagramSocket.o: DatagramSocket.cpp
	g++ -Wall -c -g DatagramSocket.cpp 
MulticastSocket.o: MulticastSocket.cpp
	g++ -Wall -c -g MulticastSocket.cpp 
emisor.o: emisor.cpp
	g++ -Wall -c -g emisor.cpp 
receptor.o: receptor.cpp
	g++ -Wall -c -g receptor.cpp 

emisor: DatagramPacket.o DatagramSocket.o MulticastSocket.o emisor.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o MulticastSocket.o emisor.o -o emisor 
receptor: DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o MulticastSocket.o receptor.o -o receptor 


clean: 
	rm *.o receptor emisor

