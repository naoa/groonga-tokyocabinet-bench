# Groonga & Tokyo Cabinet hash benchmark
## Compile
```
% make
```

## Execute

```
% ./grn_hash_bench.o 1000000
add time = 0.370000[s]
get time = 0.280000[s]

% ./tchdb_bench.o 1000000
add time = 0.530000[s]
get time = 0.540000[s]

% ls -lh groonga.grh tokyocabinet.tch
-rw-r--r-- 1 root root 65M  7月 26 21:41 2014 groonga.grh
-rw-r--r-- 1 root root 47M  7月 26 21:41 2014 tokyocabinet.tch
```
