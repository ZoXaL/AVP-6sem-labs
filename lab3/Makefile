opts = -std=c11

lab3: clean matrix.s main.s
	gcc ${opts} matrix.s main.s -o $@

matrix.s:
	gcc ${opts} -S -I. matrix.c -o $@

main.s:
	gcc ${opts} -S -I. main.c -o $@

# gcc -std=c11 -O3 -fopt-info-vec-all -I. main.c matrix2.c -o tmp

.PHONY: clean run rerun

rerun: clean lab3 run bench_cache bench

run:
	./lab3

bench_cache: clean lab3
	valgrind --tool=cachegrind ./lab3 cache	

bench: clean lab3
	valgrind --tool=cachegrind ./lab3 no-cache

clean:
	rm -f lab3
	rm -f matrix.s
	rm -f main.s
