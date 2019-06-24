.PHONY = clean


all: base

LD_PATH:
	export LD_LIBRARY_PATH=~/tel_direct/lib/

base: main.o
	gcc obj/main.o -o tel_direct -g -l dl

main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -g -I include

clean:

