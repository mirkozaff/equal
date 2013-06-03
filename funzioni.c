/**
 *  Anno Accademico: 2012-2013
 *  Corso di Studio: Informatica
 *  Titolo del progetto: Modifica utility di base di GNU/Linux
 *  Autori: Zaffaroni Mirko n° 151818
 *	Bonetta Giovanni n° 152122
 **/


#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "funzioni.h"
#include <stdarg.h>
#include <syslog.h>


boolean sameFileCheck(char * fname1, char * fname2){
    
    FILE *fp1, *fp2;
    int ch1, ch2;
    
    fp1 = fopen( fname1,  "r" );
    fp2 = fopen( fname2,  "r" ) ;

    syslog(LOG_INFO, "Verifica stesso file per %s e %s", fname1, fname2);
    
    if ( fp1 == NULL )
       {
       printf("Non riesco ad aprire %s per la lettura\n", fname1 );
       syslog(LOG_ERR, "Non riesco ad aprire %s per la lettura", fname1 );
       exit(-1);
       }
    else if (fp2 == NULL)
       {
       printf("Non riesco ad aprire %s per la lettura\n", fname2 );
       syslog(LOG_ERR, "Non riesco ad aprire %s per la lettura", fname2 );
       exit(-1);
       }
    else {
        ch1  =  getc( fp1 ) ;
        ch2  =  getc( fp2 ) ;

        while( (ch1!=EOF) && (ch2!=EOF) && (ch1 == ch2))
        {
            ch1 = getc(fp1);
            ch2 = getc(fp2) ;
        }
        
        fclose ( fp1 );
        fclose ( fp2 );

        if (ch1 == ch2){
            return TRUE;
        }
        else if (ch1 !=  ch2){            
            return FALSE;
        }    
    }
}
    
    


void safe_fopen(const char *fname, const char *mode)
{
    FILE *f = NULL;
    f = fopen(fname, mode);
    
    if (f == NULL) {
        char emsg[1024];
        sprintf(emsg, "Non riesco ad aprire %s per la lettura", fname);
        perror(emsg);
        syslog(LOG_ERR, "Non riesco ad aprire %s per la lettura", fname);
        exit(-1);
    }
    fclose(f);
    
}


boolean check_same_size(char *f1_name, char *f2_name, off_t *f1_size, off_t *f2_size)
{
    struct stat f1_stat, f2_stat;
    
    syslog(LOG_INFO, "Verifica stesso file per %s e %s", f1_name, f2_name);
    
    if((f1_name == NULL) || (f2_name == NULL)){
        fprintf(stderr, "filename non valido passato alla funzione [check_same_size].\n");
        syslog(LOG_ERR, "filename non valido passato alla funzione [check_same_size].");
        return (-1);
    }
    
    if((stat(f1_name, &f1_stat) != 0) || (stat(f2_name, &f2_stat) !=0)){
        fprintf(stderr, "Con riesco ad appilcare stat. [check_same_size].\n");
        syslog(LOG_ERR, "Non riesco ad appilcare stat. [check_same_size].");
        return (-1);
    }
    
    if(f1_size != NULL){
        *f1_size = f1_stat.st_size;
    }
    
    if(f2_size != NULL){
        *f2_size = f2_stat.st_size;
    }
    
    if(f1_stat.st_size == f2_stat.st_size) {
        return TRUE;
    }
    else {
        if(!is_binary(f1_name) && !is_binary(f2_name)){
            textDiff(f1_name, f2_name);
        }
        return FALSE;
    }
}

boolean is_file(const char* path) {
    struct stat buf;
    stat(path, &buf);
    if(S_ISREG(buf.st_mode))
        return TRUE;
    else
        return FALSE;
}

boolean is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    if(S_ISDIR(buf.st_mode))
        return TRUE;
    else
        return FALSE;
}

boolean is_binary(char * fname){
    
    FILE *fp;
    int ch;
    
    fp = fopen( fname,  "r" );
    

    if ( fp == NULL )
       {
       printf("Non riesco ad aprire %s per la lettura", fname);
       syslog(LOG_ERR, "Non riesco ad aprire %s per la lettura", fname);
       exit(-1);
       }
    else {
        ch  =  getc( fp ) ;
        while( (ch!=EOF) && (ch <= 127)){
            ch = getc(fp);
        }
        if(ch == EOF) {
           return FALSE;
        }
        else{
            return TRUE;
        }            
    }
}

void textDiff(char * fname1, char * fname2){
    
	char c1[1000]; 
	char c2[1000];
	int lineCount = 0;
    
    FILE *f1 = NULL, *f2 = NULL;
	
	f1 = fopen(fname1, "r"); 
	f2 = fopen (fname2, "r");

	printf("\n");
	
	while(fgets(c1,1000,f1) != '\0' && fgets(c2,1000,f2)!= '\0'){
		lineCount++;
		if(strcmp(c1, c2) != 0){
            printf("---------------\n");
            printf("Linea %d diversa:\n", lineCount);
            printf("%s\n",c1);
            printf("%s\n",c2);
            printf("---------------\n");
        }
    }
    
	fclose(f1);
	fclose(f2);
}

boolean scanDir(char *dir, char* filename){
    
    DIR * dp;
        
    struct dirent *entry;
    struct stat statbuf;
    
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"Non riesco ad aprire %s per la lettura: \n", dir);
        syslog(LOG_ERR, "Non riesco ad aprire %s per la lettura", dir);
        exit(-1); 
    }

    chdir(dir);

    while((entry = readdir(dp)) != NULL) {
        stat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            continue;
        }
        if(S_ISREG(statbuf.st_mode)){
            
            if(strcmp(filename, entry->d_name) == 0){
                if(twoFilesCompare(filename, entry-> d_name)){
                    chdir("..");
                    closedir(dp);
                    return TRUE;
                }
                else{
                    chdir("..");
                    closedir(dp);
                    return FALSE;
                }
            }
        }
    }
    
    printf("File non presente nella directory\n");
    syslog(LOG_ERR, "File non presente nella directory");
    exit(-1);    
}

boolean twoFilesCompare(char *fname1, char *fname2){
    
    safe_fopen(fname1, "r");
    safe_fopen(fname2, "r");

    if(is_binary(fname1) && is_binary(fname2)){

        if(!check_same_size(fname1, fname2, NULL, NULL)){
            return FALSE;
        }
        else{
            if(sameFileCheck(fname1, fname2)){
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
    }
    else if(!is_binary(fname1) && !is_binary(fname2)){

        if(!check_same_size(fname1, fname2, NULL, NULL)){
            return FALSE;
        }
        else{
            if(sameFileCheck(fname1, fname2)){                    
                return TRUE;
            }
            else{
                textDiff(fname1, fname2);
                return FALSE;
            }
        }
    }
    else{
        return FALSE;
    }
}

void scorriCartelle(char *dir1, char *dir2){
    
    DIR * dp1;
        
    struct dirent *entry1;
        
    if((dp1 = opendir(dir1)) == NULL) {
        fprintf(stderr,"Non riesco ad aprire %s per la lettura: \n", dir1);
        syslog(LOG_ERR, "Non riesco ad aprire %s per la lettura", dir1);
        exit(-1); 
    }

    while((entry1 = readdir(dp1)) != NULL) {
        
        /* Ignora le cartelle ".." e "." */
        if(strcmp(".", entry1-> d_name) == 0 || strcmp("..", entry1->d_name) == 0){
                continue;
        
        }
        
        if(is_file(entry1 -> d_name)){
            if(findFile(entry1->d_name, dir2)){
                if(!twoFilesCompare(superStringsCat(dir1, "/", entry1->d_name, NULL), superStringsCat(dir2, "/", entry1->d_name, NULL))){
                    printf("I Files %s/%s e %s/%s sono diversi\n", dir1, entry1->d_name, dir2, entry1->d_name);
                }                
            }    
            else{
                printf("Solo in %s: %s\n", dir1, entry1->d_name);
            }           
        }        
        
        if(is_dir(entry1 -> d_name)) { 
            if(findDir(entry1->d_name, dir2)){
                printf("Sottodirectory in comune: %s/%s e %s/%s\n", dir1, entry1->d_name, dir2, entry1->d_name);
            }
            else{
                printf("Solo in %s: %s\n", dir1, entry1->d_name);
            }
        }
    }      
}

boolean findDir(char *dir1, char* dir2){
    
    DIR *dp2;
    
    struct dirent *entry2;
    struct stat statbuf2;
    
    if((dp2 = opendir(dir2)) == NULL) {
        fprintf(stderr,"Non riesco ad aprire %s per la lettura: \n", dir2);
        syslog(LOG_ERR, "Non riesco ad aprire %s per la lettura", dir2);
        exit(-1); 
    }
    
    while((entry2 = readdir(dp2)) != NULL){
        stat(entry2->d_name,&statbuf2);
        if(S_ISDIR(statbuf2.st_mode)){
            if(strcmp(dir1, entry2->d_name) == 0){
                return TRUE;
            }
        }
    }
    return FALSE;
}

boolean findFile(char *f1, char* dir2){
    
    DIR *dp2;
    
    struct dirent *entry2;
    struct stat statbuf2;
    
    if((dp2 = opendir(dir2)) == NULL) {
        fprintf(stderr,"Non riesco ad aprire %s per la lettura: \n", dir2);
        syslog(LOG_ERR, "Non riesco ad aprire %s per la lettura", dir2);
        exit(-1); 
    }
    
    while((entry2 = readdir(dp2)) != NULL){
        lstat(entry2->d_name,&statbuf2);
        if(S_ISREG(statbuf2.st_mode)){
            if(strcmp(f1, entry2->d_name) == 0){
                
                return TRUE;
            }
        }
    }
    return FALSE;
}

char *superStringsCat(char *String1, ...){
    
	va_list List;	
	va_start (List, String1);
	
	unsigned int Size;
	
	Size = strlen (String1) + 1;
	
	char *s;
	s = String1;
	
	do
	{
		Size += strlen (s) + 1;
	}while ((s = va_arg (List, char*)) != NULL);
	
	char *Merge;
	Merge = (char*)malloc (sizeof (char) * Size);
	char *sMerge = Merge;

	va_end (List);
	va_start (List, String1);

	s = String1;
	
	do
	{
		strcpy (Merge, s);
		Merge += strlen (s);
	}while ((s = va_arg (List, char*)) != NULL);
	
	va_end (List);
	
	return sMerge;
}