CFLAGS = -g -Wall -std=c99
DCFLAGS = -g -Wall -std=c99 -o0

all: presmash rules.d smash

presmash: smash.o
	gcc -c -Wall smash.c -o smash.o

smash:  smash.o smashLib.a Makefile
	gcc $(CFLAGS) -o smash smash.o smashLib.a

smashLib.a: commands.o history.o
	ar r smashLib.a commands.o history.o

debug: smash.o commands.o history.o  Makefile
	gcc $(DCFLAGS) -o dsmash smash.o commands.o history.o

valgrind: debug
	valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all  smash

clean:	
	rm -f *.o *.a smash dsmash
	
#Rebuild rules.d if it’s out-of-date with any *.c or *.h file using gcc -MM
rules.d: $(wildcard *.c) $(wildcard *.h)
	gcc -MM $(wildcard *.c) >rules.d

#Incorporate the auto-generated dependencies from rules.d into this Makefile
-include rules.d
