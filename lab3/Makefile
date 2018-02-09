opts = -std=c11

lab3: clean main.c
	gcc ${opts} main.c gnuplot_i.o -o $@


.PHONY: clean run rerun

bench: lab3 
	valgrind --tool=cachegrind ./lab3 ${d}

plot: lab3 
	./lab3 plot

run:
	./lab3

clean:
	rm -f lab3
