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



void printdir(char *dir, int depth)
{/*
    DIR * dp;
        
    struct dirent *entry;
    struct stat statbuf;
    
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }

    chdir(dir);

    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            // Found a directory, but ignore . and ..
            if(strcmp(".", entry-> d_name) == 0 || strcmp("..", entry->d_name) == 0){
                continue;
            }
            printf("%*s%s/\n", depth,"", entry->d_name);
            /* Recurse at a new indent level */
    /*        printdir(entry->d_name,depth+4);
        }
        else {
        	printf("%*s%s\n", depth, "", entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
*/}


boolean sameFileCheck(char * fname1, char * fname2){
    
    FILE *fp1, *fp2;
    int ch1, ch2;
    
    fp1 = fopen( fname1,  "r" );
    fp2 = fopen( fname2,  "r" ) ;

    if ( fp1 == NULL )
       {
       printf("Non riesco ad aprire %s per la letturag\n", fname1 );
       exit(1);
       }
    else if (fp2 == NULL)
       {
       printf("Non riesco ad aprire %s per la lettura\n", fname2 );
       exit(1);
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
        sprintf(emsg, "Cannot open file: %s", fname);
        perror(emsg);
        exit(-1);
    }
    fclose(f);
    
}


boolean check_same_size(const char *f1_name, const char *f2_name, off_t *f1_size, off_t *f2_size)
{
    struct stat f1_stat, f2_stat;
    
    if((f1_name == NULL) || (f2_name == NULL)){
        fprintf(stderr, "Invalid filename passed to function [check_same_size].\n");
        return (-1);
    }
    
    if((stat(f1_name, &f1_stat) != 0) || (stat(f2_name, &f2_stat) !=0)){
        fprintf(stderr, "Cannot apply stat. [check_same_size].\n");
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
        return FALSE;
    }
}

/*
int check_dup_plain(char *f1_name, char *f2_name, int block_size)
{
    if ((f1_name == NULL) || (f2_name == NULL)){
        fprintf(stderr, "Invalid filename passed to function [check_dup_plain].\n");
        return (-1);
    }
    
    FILE *f1 = NULL, *f2 = NULL;
    char f1_buff[block_size], f2_buff[block_size];
    size_t rch1, rch2;
    
    if(check_same_size(f1_name, f2_name, NULL, NULL) == 1){
        return (1);
    }
    
    f1 = safe_fopen(f1_name, O_RDONLY);
    f2 = safe_fopen(f2_name, O_RDONLY);
    
    while(!feof(f1) && !feof(f2)){
        rch1 = fread(f1_buff, 1, block_size, f1);
        rch2 = fread(f2_buff, 1, block_size, f2);
        if(rch1 != rch2){
            fprintf(stderr, "Invalid reading from file. Cannot continue. [check_dup_plain].\n");
            return (-1);
        }
        while(rch1-->0){
            if(f1_buff[rch1] != f2_buff[rch1]){
                return (1);
            }
        }
    }
    
    fclose(f1);
    fclose(f2);
    
    return (0);
}
*/
/*
int check_dup_memmap(char *f1_name, char *f2_name)
{
    struct stat f1_stat, f2_stat;
    char *f1_array = NULL, *f2_array = NULL;
    off_t f1_size, f2_size;
    int f1_des, f2_des, cont, res;
    
    if((f1_name == NULL) || (f2_name == NULL)){
        fprintf(stderr, "Invalid filename passed to function [check_dup_memmap].\n");
        return (-1);    
    }
    
    if(check_same_size(f1_name, f2_name, &f1_size, &f2_size) == 1){
        return (1);
    }
    
    f1_des = open(f1_name, O_RDONLY);
    f2_des = open(f2_name, O_RDONLY);
    
    if((f1_des == -1) || (f2_des == -1)){
        perror("Cannot open file");
        exit(-1);       
    }
    
    f1_array = mmap(0, f1_size * sizeof(*f1_array), PROT_READ, MAP_SHARED, f1_des, 0);
    
    if(f1_array == NULL){
        fprintf(stderr, "Cannot map file to memory [check_dup_memmap].\n");
        return (-1);
    }
    
    f2_array = mmap(0, f2_size * sizeof(*f2_array), PROT_READ, MAP_SHARED, f2_des, 0);
    
    if(f2_array == NULL){
        fprintf(stderr, "Cannot map file to memory [check_dup_memmap].\n");
        return (-1);
    }
    
    cont = f1_size;
    res = 0;
    
    while(cont-->0){
        if(f1_array[cont]!=f2_array[cont]){
            res = 1;
            break;
        }
    }
    
    munmap((void*) f1_array, f1_size * sizeof(*f1_array));
    munmap((void*) f2_array, f2_size * sizeof(*f2_array));
    
    return res;
}*/

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

void stampadir(char *path){
    
    DIR * d;
	struct dirent *dir;
	d = opendir(path);
	if (d != NULL)  {
		while ((dir = readdir(d)) != NULL) {
			if(strcmp(".", dir -> d_name) == 0 || strcmp("..", dir -> d_name) == 0){
				continue;
			}
			printf("%s\n", dir -> d_name);
		}

    closedir(d);
 	}
}

boolean is_binary(char * fname){
    
    FILE *fp;
    int ch;
    
    fp = fopen( fname,  "r" );
    

    if ( fp == NULL )
       {
       printf("Cannot open %s for reading ", fname);
       exit(1);
       }
    else {
        ch  =  getc( fp ) ;
        while( (ch!=EOF) && (ch >= 0) && (ch <= 127)){
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
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }

    chdir(dir);

    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
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