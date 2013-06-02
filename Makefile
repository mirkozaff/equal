#
# Makefile equal
# Sistema operativo Linux con compilatore gcc 4.7.3
#
mkbkp: equal.o funzioni.o
	gcc -o equal equal.o funzioni.o
#
mkbkp.o: mkbkp.c
	gcc -c equal.c
#
funzioni.o: funzioni.c
	gcc -c funzioni.c
