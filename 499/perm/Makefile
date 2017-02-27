all: solveGrid.out genv2.out genv1.out scatter.out genv3.out

solveGrid.out: solveGrid.c
	mpic++ --std=c++11 solveGrid.c -o solveGrid.out

genv1.out: genv1.c
	mpic++ --std=c++11 genv1.c -o genv1.out
genv2.out: genv2.c
	mpic++ --std=c++11 genv2.c -o genv2.out
genv3.out: genv3.c
	mpic++ --std=c++11 genv3.c -o genv3.out
scatter.out: scatter.c
	mpic++ --std=c++11 scatter.c -o scatter.out

clean:
	rm *.out
