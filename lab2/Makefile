opts = -fopenmp ${d} -std=c11

lab2: matrix2.s main.s
	gcc ${opts} $^ -o $@

matrix2.s:
	gcc ${opts} -S -I. matrix2.c -o $@

main.s:
	gcc ${opts} -S -I. main.c -o $@

# gcc -std=c11 -O3 -fopt-info-vec-all -I. main.c matrix2.c -o tmp

.PHONY: clean

clean:
	rm -f lab2
	rm -f matrix2.s
	rm -f main.s
