
ifeq ($(uname_S), Linux)
	v_client = client
	v_server = server
else
    v_client = client_win
    v_server = server_win
endif



all: $(v_client) $(v_server)

client_win: DatagramPacket.o DatagramSocket.o Message.o Request.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o Request.o client.cpp -o client -lwsock32
server_win: DatagramPacket.o DatagramSocket.o Message.o Reply.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o Reply.o   server.cpp -o server -lwsock32

client: DatagramPacket.o DatagramSocket.o Message.o Request.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o Request.o client.cpp -o client
server: DatagramPacket.o DatagramSocket.o Message.o Reply.o
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

debug:
	g++ -g3 -Wall DatagramPacket.cpp DatagramSocket.cpp Message.cpp Request.cpp client.cpp -o client
	g++ -g3 -Wall DatagramPacket.cpp DatagramSocket.cpp Message.cpp Reply.cpp server.cpp -o server

clear:
	rm -rf *.o *.exe client server
