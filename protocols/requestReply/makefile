
all: client server

debug:
	g++ -g3 DatagramPacket.cpp DatagramSocket.cpp Request.cpp client.cpp -o client
	g++ -g3 DatagramPacket.cpp DatagramSocket.cpp Reply.cpp server.cpp -o server

client: DatagramPacket.o DatagramSocket.o client.o Request.o
	g++ -g3 DatagramPacket.o DatagramSocket.o Request.o client.cpp -o client
server: DatagramPacket.o DatagramSocket.o server.o Reply.o
	g++ -g3 DatagramPacket.o DatagramSocket.o Reply.o server.cpp -o server

DatagramPacket.o: DatagramPacket.cpp
	g++ -c DatagramPacket.cpp -Wall
DatagramSocket.o: DatagramSocket.cpp
	g++ -c DatagramSocket.cpp -Wall
Reply.o: Reply.cpp
	g++ -c Reply.cpp -Wall
Request.o: Request.cpp
	g++ -c Request.cpp -Wall



clear:
	rm -rf *.o *.exe client server
