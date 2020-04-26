
all: client server

client: DatagramPacket.o DatagramSocket.o client.o
	g++ DatagramPacket.o DatagramSocket.o client.o -o client
server: DatagramPacket.o DatagramSocket.o server.o
	g++ DatagramPacket.o DatagramSocket.o server.cpp -o server

DatagramPacket.o: DatagramPacket.cpp
	g++ -c DatagramPacket.cpp -Wall
DatagramSocket.o: DatagramSocket.cpp
	g++ -c DatagramSocket.cpp -Wall
client.o: client.cpp
	g++ -c client.cpp -Wall
server.o: server.cpp
	g++ -c server.cpp -Wall

clear:
	rm -rf *.o *.exe client server
