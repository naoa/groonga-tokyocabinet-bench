CC = gcc
CFLAGS = -Wall -O2 -lgroonga -I/usr/include/groonga -ltokyocabinet

all: grn_hash_bench tchdb_bench 

grn_hash_bench : src/grn_hash_bench.c
	$(CC) src/grn_hash_bench.c -o grn_hash_bench $(CFLAGS)

tchdb_bench : src/tchdb_bench.c
	$(CC) src/tchdb_bench.c -o tchdb_bench $(CFLAGS)

clean:
	rm -rf grn_hash_bench tchdb_bench groonga.grh tokyocabinet.tch

