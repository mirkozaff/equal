#ifndef FUNZIONI_H
#define	FUNZIONI_H


#include <sys/types.h>
#include <stdio.h>


/**
 * Definizione di boolean.
 **/
typedef enum {FALSE = 0, TRUE = 1} boolean;


/** 
 * Controllo se due file sono uguali stringa per stringa.
 **/
boolean sameFileCheck(char* fname1, char* fname2);


/**
* Assicura che il file venga aperto.
* Se non può aprire il programma il programma viene interrotto.
* Il codice di errore ritornato: -1.
**/
void safe_fopen(const char *fname, const char *mode);


/**
* Controlla se due file hanno la stessa dimensione.
* Ritorna:
* -1    Errore.
* 0 Se hanno la stessa dimensione.
* 1 Se non hanno la stessa dimensione.
**/
boolean check_same_size(const char *f1_name, const char *f2_name, off_t *f1_size, off_t *f2_size);


/*
 * Controlla se il path passato corrisponde ad una directory
 * TRUE se lo è
 * FALSE altrimenti
 */
boolean is_dir(const char* path);
 

/*
 * Controlla se il path passato corrisponde ad un file
 * TRUE se lo è
 * FALSE altrimenti
 */
boolean is_file(const char* path);


/**
 * Controlla se un file è binario
 * TRUE se lo è
 * FALSE altrimenti
 **/
boolean is_binary(char * fname);


/**
 * Confronta due file di testo e ritorna
 * a video le righe di differenza
 **/
void textDiff(char * fname1, char * fname2);

/**
 * Confronta due file per trovarne le uguaglianze
 * TRUE se sono uguali
 * FALSE altrimenti
 **/
boolean twoFilesCompare(char *fname1, char *fname2);


/**
 * Scorre una directory in cerca del file passato
 * come argomento
 * TRUE se la trova
 * FALSE altrimenti
 **/
boolean scanDir(char *dir, char* filename);


/**
 * Cerca le directory con lo stesso nome
 * all'interno di una directory
 * TRUE se la trova
 * FALSE altrimenti
 **/
boolean findDir(char *dir1, char* dir2);


/**
 * Cerca i file con lo stesso nome
 * all'interno di una directory
 * TRUE se la trova
 * FALSE altrimenti
 **/
boolean findFile(char *f1, char* dir2);


/**
 * Scorre le cartelle cercando le corrispondenza 
 * tra la prima e la seconda cartella
 * passate in argomento.
 **/
void scorriCartelle(char *dir1, char *dir2);


/**
 * Concatena tutte le stringe prese in argomento,
 *  finchè non trova la stringa a NULL
 **/
char *superStringsCat(char *String1, ...);


#endif	/* FUNZIONI_H */

