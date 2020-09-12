CFLAGS = -g -Wall -std=c99

all: rules.d sed253

sed253: copy.o delete.o substitute.o sed253.o Makefile
	gcc $(CFLAGS) -o sed253 copy.o delete.o substitute.o sed253.o

clean:	
	rm -f *.o sed253
	
#Rebuild rules.d if it’s out-of-date with any *.c or *.h file using gcc -MM
rules.d: $(wildcard *.c) $(wildcard *.h)
	gcc -MM $(wildcard *.c) >rules.d

#Incorporate the auto-generated dependencies from rules.d into this Makefile
-include rules.d
