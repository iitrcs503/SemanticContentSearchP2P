CC = gcc

CFLAGS = -lm -pthread -O3 -march=native -Wall -funroll-loops -Wno-unused-result

all: word2vec semanticSearch

word2vec : word2vec.c
	$(CC) word2vec.c -o word2vec $(CFLAGS)

semanticSearch : semanticSearch.c
	$(CC) semanticSearch.c -o semanticSearch $(CFLAGS)


	chmod +x *.sh

clean:
	rm -rf word2vec semanticSearch
