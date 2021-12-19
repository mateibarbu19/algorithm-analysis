CC = g++
CFLAGS = -Wall -Wextra -O2
DEBUG =# -g -ggdb
LDLIBS = -lm
SOURCES = ./src


build: lca_disjoint-set lca_rmq

lca_disjoint-set: main.o lca_disjoint-set.o
	g++ main.o lca_disjoint-set.o $(CFLAGS) $(DEBUG) -o lca_disjoint-set

lca_rmq: main.o lca_rmq.o
	g++ main.o lca_rmq.o $(CFLAGS) $(DEBUG) -o lca_rmq

lca_disjoint-set.o: $(SOURCES)/lca_disjoint-set.cpp
	g++ $(SOURCES)/lca_disjoint-set.cpp -c $(CFLAGS) $(DEBUG) -o lca_disjoint-set.o

lca_rmq.o: $(SOURCES)/lca_rmq.cpp
	g++ $(SOURCES)/lca_rmq.cpp -c $(CFLAGS) $(DEBUG) -o lca_rmq.o

main.o: $(SOURCES)/main.cpp
	g++ $(SOURCES)/main.cpp -c $(CFLAGS) $(DEBUG) -o main.o

run_tests:
	./checker/checker.sh

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf lca_disjoint-set
	rm -rf lca_rmq
