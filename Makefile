#
#  Anno Accademico: 2012-2013
#  Corso di Studio: Informatica
#  Titolo del progetto: Modifica utility di base di GNU/Linux
#  Autori: Zaffaroni Mirko n° 151818
#	   Bonetta Giovanni n° 152122
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
