zw2c4svxall:SR.o ST.o
	gcc -o output main.c
	./output

SR.o:SR.c
	gcc -o SR.o SR.c
	gcc -o SR SR.c

ST.o:ST.c
	gcc -o ST.o ST.c
	gcc -o ST ST.c

clean:
	rm -f *.o SR run2 output Q1 *.s *.out