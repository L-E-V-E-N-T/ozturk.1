output: program5_2.o
	gcc program5_2.o -o output

program5_2.o: program5_2.c
	gcc -c program5_2.c

clean:
	rm *.o output
