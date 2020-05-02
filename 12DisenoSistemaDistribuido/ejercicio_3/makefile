
all: client server

client: client.o DatagramPacket.o DatagramSocket.o reg_util.o
	g++ -g -Wall client.o DatagramPacket.o DatagramSocket.o reg_util.o -o client
server: server.o DatagramPacket.o DatagramSocket.o reg_util.o
	g++ -g -Wall server.o DatagramPacket.o DatagramSocket.o reg_util.o -o server

DatagramPacket.o: ./lib/DatagramPacket.cpp
	g++ -c -g -Wall ./lib/DatagramPacket.cpp
DatagramSocket.o: ./lib/DatagramSocket.cpp
	g++ -c -g -Wall ./lib/DatagramSocket.cpp
reg_util.o: ./lib/reg_util.cpp
	g++ -c -g -Wall ./lib/reg_util.cpp

client.o: client.cpp
	g++ -c -g -Wall client.cpp
server.o: server.cpp
	g++ -c -g -Wall server.cpp

clean: 
	rm *.o client server
