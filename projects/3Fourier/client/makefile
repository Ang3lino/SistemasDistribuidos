 
ifeq ($(OS),Windows_NT)
	flags = -lwsock32
else 
	flags = 
endif

generator: DatagramPacket.o DatagramSocket.o Message.o ByteBuffer.o generator.o
	g++ -g3 -Wall DatagramPacket.o DatagramSocket.o Message.o ByteBuffer.o generator.o -o generator $(flags)

generator.o: generator.cpp
	g++ -c -g3 -Wall generator.cpp
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

clear:
	del *.o 
	del *.exe 
	del *~ 

clear_lin:
	rm -rf *.o *.exe client server