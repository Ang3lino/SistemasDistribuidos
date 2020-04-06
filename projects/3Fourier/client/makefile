 
ifeq ($(OS),Windows_NT)
	v_client = client_win
	v_server = server_win
	flags = -lwsock32
else 
	v_client = client
	v_server = server
	flags = 
endif

# all: $(v_client) $(v_server)

generator: DatagramPacket.o DatagramSocket.o Message.o ByteBuffer.o 
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o ByteBuffer.o generator.cpp -o generator $(flags)

client_win: DatagramPacket.o DatagramSocket.o Message.o Request.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o Request.o client.cpp -o client -lwsock32
server_win: DatagramPacket.o DatagramSocket.o Message.o Reply.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o Reply.o   server.cpp -o server -lwsock32

client: DatagramPacket.o DatagramSocket.o Message.o Request.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o Request.o client.cpp -o client
server: DatagramPacket.o DatagramSocket.o Message.o Reply.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o Reply.o server.cpp -o server

ByteBuffer.o: ByteBuffer.cpp
	g++ -c -g3 -Wall ByteBuffer.cpp
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

clear_lin:
	rm -rf *.o *.exe client server

clear_win:
	del *.o 
	del *.exe 
	del *~ 
