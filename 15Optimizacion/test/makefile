
all: search

search: reg_util.o search.cpp
	g++ -g -Wall reg_util.o ../Trie.cpp search.cpp -o search

reg_util.o: ../lib/reg_util.cpp
	g++ -c -g -Wall ../lib/reg_util.cpp

clean: 
	rm *.o search
