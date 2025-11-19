.PHONY: build main clean exe

build: main.o
	gcc main.o -o ASCIImages -lncurses
	$(MAKE) clean

main.o:
	gcc -c main.c

clean:
	rm -rf *.o

exe:
	$(MAKE) build
	./ASCIImages
