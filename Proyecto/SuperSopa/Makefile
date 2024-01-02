FLAGS = -O2 -std=c++11


all: diccSortedVector.o diccTrie.o diccBloomFilter.o diccDHashing.o main.o main.x 

diccSortedVector.o: diccSortedVector.cc
	g++ -c diccSortedVector.cc $(FLAGS)

diccTrie.o: diccTrie.cc
	g++ -c diccTrie.cc $(FLAGS)

diccBloomFilter.o: diccBloomFilter.cc
	g++ -c diccBloomFilter.cc $(FLAGS)

diccDHashing.o: diccDHashing.cc
	g++ -c diccDHashing.cc $(FLAGS)

main.o: main.cc
	g++ -c main.cc $(FLAGS)


main.x: main.o diccSortedVector.o diccBloomFilter.o diccTrie.o diccDHashing.o
	g++ -o main.x *.o $(FLAGS)

clean:
	rm *.o
	rm main.x
