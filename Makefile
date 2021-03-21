DEBUG_FLAGS = -g -Wall -ggdb3
VALGRING_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt

default: colecao-teste.c plantas.o
	gcc colecao-teste.c plantas.o -o colecao.out
	rm plantas.o

plantas.o: plantas.c plantas.h
	gcc plantas.c -c

clean: 
	rm *.out *out.txt

debug: colecao-teste.c plantas.debug
	gcc $(DEBUG_FLAGS) -o debug_build.out colecao-teste.c plantas.debug
	rm plantas.debug

plantas.debug: plantas.c plantas.h
	gcc $(DEBUG_FLAGS) -c plantas.c -o plantas.debug

valgrind:
	valgrind $(VALGRING_FLAGS) ./debug_build.out 