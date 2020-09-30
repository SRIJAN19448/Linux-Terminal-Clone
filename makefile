all: compile run

compile:shell11.c ls.c cat.c mkdir.c rm.c date.c
	gcc shell11.c -o shell11.out
	gcc ls.c -o ls.out
	gcc cat.c -o cat.out
	gcc mkdir.c -o mkdir.out
	gcc rm.c -o rm.out
	gcc date.c -o date.out

run:shell11.out
	./shell11.out

clean:
	rm *.out