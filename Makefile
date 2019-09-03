output: main.o
	gcc main.o -o dt

program5_2.o: main.c
	gcc -c main.c

clean:
	rm *.o dt
