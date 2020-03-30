
all: client server

debug:
	g++ -g3 -Wall DatagramPacket.cpp DatagramSocket.cpp Message.cpp Request.cpp client.cpp -o client
	g++ -g3 -Wall DatagramPacket.cpp DatagramSocket.cpp Message.cpp Reply.cpp server.cpp -o server

client: DatagramPacket.o DatagramSocket.o client.o Message.o Request.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o Request.o client.cpp -o client
server: DatagramPacket.o DatagramSocket.o server.o Message.o Reply.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o Reply.o server.cpp -o server

Message.o: Message.cpp
	g++ -c -g3 -Wall Message.cpp
DatagramPacket.o: DatagramPacket.cpp
	g++ -c -g3 -Wall DatagramPacket.cpp 
DatagramSocket.o: DatagramSocket.cpp
	g++ -c -g3 -Wall DatagramSocket.cpp 
Reply.o: Reply.cpp
	g++ -c -g3 -Wall Reply.cpp 
Request.o: Request.cpp
	g++ -c -g3 -Wall Request.cpp 



clear:
	rm -rf *.o *.exe client server
