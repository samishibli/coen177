# Makefile to compile all C programs (Steps 2–5)

all: step2 step3 step4 step5

step2: step2.c
	gcc -o step2 step2.c

step3: step3.c
	gcc -o step3 step3.c

step4: step4.c
	gcc -o step4 step4.c

step5: step5.c
	gcc -o step5 step5.c -lpthread

clean:
	rm -f *.out step2 step3 step4 step5
