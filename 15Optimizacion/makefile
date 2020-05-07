
all: client server

client: client.o DatagramPacket.o DatagramSocket.o reg_util.o Request.o Message.o 
	g++ -g -Wall client.o DatagramPacket.o DatagramSocket.o reg_util.o Request.o Message.o Trie.cpp -o client
server: server.o DatagramPacket.o DatagramSocket.o reg_util.o Message.o Reply.o
	g++ -g -Wall server.o DatagramPacket.o DatagramSocket.o reg_util.o Message.o Reply.o -o server

DatagramPacket.o: ./lib/DatagramPacket.cpp
	g++ -c -g -Wall ./lib/DatagramPacket.cpp
DatagramSocket.o: ./lib/DatagramSocket.cpp
	g++ -c -g -Wall ./lib/DatagramSocket.cpp
reg_util.o: ./lib/reg_util.cpp
	g++ -c -g -Wall ./lib/reg_util.cpp

Request.o: ./lib/Request.cpp
	g++ -c -g -Wall ./lib/Request.cpp
Reply.o: ./lib/Reply.cpp
	g++ -c -g -Wall ./lib/Reply.cpp
Message.o: ./lib/Message.cpp
	g++ -c -g -Wall ./lib/Message.cpp

client.o: client.cpp
	g++ -c -g -Wall client.cpp
server.o: server.cpp
	g++ -c -g -Wall server.cpp

clean: 
	rm *.o client server
