
all: webserver receptor

webserver: server3.o DatagramPacket.o DatagramSocket.o MulticastSocket.o Request.o Message.o mongoose.o
	g++ -g -Wall server3.o DatagramPacket.o DatagramSocket.o MulticastSocket.o Request.o Message.o mongoose.o -o webserver
receptor: receptor.o DatagramPacket.o DatagramSocket.o MulticastSocket.o reg_util.o Message.o Reply.o sqlite3.o dbase.o
	g++ -g -Wall receptor.o DatagramPacket.o DatagramSocket.o reg_util.o MulticastSocket.o Message.o Reply.o sqlite3.o dbase.o -o receptor -pthread -ldl

server3.o: server3.cpp
	g++ -c -g server3.cpp -Wall
mongoose.o: mongoose.c
	gcc -c mongoose.c
sqlite3.o: ./lib/sqlite3.h
	gcc -c ./lib/sqlite3.c -pthread -ldl
dbase.o: ./lib/dbase.h
	g++ -c ./lib/dbase.cpp # sqlite3.o -pthread -ldl

DatagramPacket.o: ./lib/DatagramPacket.cpp
	g++ -c -g -Wall ./lib/DatagramPacket.cpp
MulticastSocket.o: ./lib/MulticastSocket.cpp
	g++ -c -g -Wall ./lib/MulticastSocket.cpp
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

emisor.o: emisor.cpp
	g++ -c -g -Wall emisor.cpp
receptor.o: receptor.cpp
	g++ -c -g -Wall receptor.cpp

clean: 
	rm *.o webserver receptor
