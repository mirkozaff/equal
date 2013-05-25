#ifndef FUNZIONI_H
#define	FUNZIONI_H


#include <sys/types.h>
#include <stdio.h>


/**
 * Definizione di boolean
 **/
typedef enum {FALSE = 0, TRUE = 1} boolean;

/** 
 * Stampa di directory
 **/
void printdir(char *dir, int depth);

/** 
 * Controllo se due file sono uguali stringa per stringa
 **/
void sameFileCheck(char* fname1, char* fname2);

/**
* Safely assures that a file is opened. 
* If cannot open file, the flow of the program is interrupted.
* The error code returned is -1.
**/
FILE *safe_fopen(const char *fname, const char *mode);


/**
* Check if two files have the same size.
* Returns:
* -1    Error.
* 0 If they have the same size.
* 1 If the don't have the same size.
**/
int check_same_size(const char *f1_name, const char *f2_name, off_t *f1_size, off_t *f2_size);


/**
* Test if two files are duplicates.
* Returns:
* -1    Error.
* 0 If they are duplicates.
* 1 If they are not duplicates.
**/
int check_dup_plain(char *f1_name, char *f2_name, int block_size);

/**
* Test if two files are duplicates.
* Returns:
* -1    Error.
* 0 If they are duplicates.
* 1 If they are not duplicates.
**/
int check_dup_memmap(char *f1_name, char *f2_name);

boolean is_dir(const char* path);
        
boolean is_file(const char* path);

#endif	/* FUNZIONI_H */

